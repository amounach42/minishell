/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   almost_six.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amounach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 14:59:44 by iel-bakk          #+#    #+#             */
/*   Updated: 2023/01/07 21:14:42 by amounach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redir	*creat_redir_node(char *file_name, int type)
{
	t_redir	*tmp;

	tmp = (t_redir *)malloc(sizeof(t_redir));
	if (!tmp)
		return (NULL);
	tmp->file_name = file_name;
	tmp->type = type;
	tmp->next = NULL;
	return (tmp);
}

t_final	*creat_final_node(int tab_len)
{
	t_final	*tmp;

	tmp = (t_final *)malloc(sizeof(t_final));
	if (!tmp)
		return (NULL);
	tmp->list = NULL;
	tmp->next = NULL;
	tmp->str = (char **)malloc(sizeof(char *) * (tab_len + 1));
	if (!tmp->str)
	{
		free(tmp);
		return (NULL);
	}
	return (tmp);
}

int	verify_is_redir_type(t_tokens *test)
{
	if (test == NULL)
		return (0);
	if (test->type == RE_INPUT || test->type == RE_OUTPUT
		|| test->type == APPEND || test->type == HEREDOC)
		return (1);
	return (0);
}

int	verify_is_word_type(t_tokens *test)
{
	if (!test)
		return (0);
	if (test->type == WORD || test->type == DOUBLE_Q || test->type == SINGLE_Q
		|| test->type == VARIABLE)
		return (1);
	return (0);
}

int	calc_cmd_len(t_tokens *list)
{
	int	len;

	len = 0;
	while (list)
	{
		if (verify_is_word_type(list) && verify_is_word_type(list->next)
			&& list->space == 0)
			list = list->next;
		else if (verify_is_redir_type(list) && verify_is_word_type(list->next))
			list = list->next->next;
		else if (verify_is_word_type(list) && list->space)
		{
			len++;
			list = list->next;
		}
		else if (verify_is_word_type(list) && (list->next == NULL
				|| !verify_is_word_type(list->next)))
		{
			len++;
			list = list->next;
		}
		else
			break ;
	}
	return (len);
}

void	add_final_end(t_final **head, t_final *new)
{
	t_final	*tmp;

	tmp = *head;
	if (*head == NULL)
		*head = new;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void	free_redir_node(t_redir *f)
{
	free(f->file_name);
	free(f);
}

void	add_redir_end(t_redir **head, t_redir *new)
{
	t_redir	*tmp;

	if (*head == NULL)
		*head = new;
	else
	{
		tmp = *head;
		while (tmp->next)
		{
			tmp = tmp->next;
		}
		tmp->next = new;
	}
}

void	final_command_helper(t_final *command, t_tokens **buff, char **tmp,
		int *i)
{
	if (verify_is_redir_type(*buff))
	{
		add_redir_end(&command->list, get_redir_list(buff));
		return ;
	}
	if ((*buff)->space == 0 && (*buff)->next
		&& verify_is_word_type((*buff)->next))
	{
		if (*tmp)
			*tmp = ft_strjoin(*tmp, (*buff)->next->value);
		else
			*tmp = ft_strjoin((*buff)->value, (*buff)->next->value);
		*buff = (*buff)->next;
		return ;
	}
	if (*tmp)
	{
		command->str[(*i)++] = ft_strdup(*tmp);
		free(*tmp);
		*tmp = NULL;
	}
	else
		command->str[(*i)++] = ft_strdup((*buff)->value);
	(*buff) = (*buff)->next;
}

void	final_command(t_final **head, t_tokens **list, int len)
{
	t_final		*command;
	char		*tmp;
	t_tokens	*buff;
	int			i;

	if (!list || !(*list))
		return ;
	command = creat_final_node(len);
	if (!command)
		return ;
	tmp = NULL;
	buff = *list;
	i = 0;
	while (buff && buff->type != PIPE)
		final_command_helper(command, &buff, &tmp, &i);
	command->str[len] = NULL;
	*list = buff;
	add_final_end(head, command);
}

t_final	*convert_from_tokens_to_final(t_tokens *list)
{
	t_final	*head;

	head = NULL;
	if (!list)
		return (NULL);
	if (list->type == NONE)
		list = list->next;
	while (list)
	{
		if (verify_is_word_type(list) || verify_is_redir_type(list))
			lvlup_ultimate(&list, &head);
		else
		{
			list = list->next;
			lvlup_ultimate(&list, &head);
		}
	}
	return (head);
}

int	get_redir_list_helper(t_tokens **tmp, char **buff, t_redir *head)
{
	if ((*tmp)->space == 0 && (*tmp)->next && verify_is_word_type((*tmp)->next))
	{
		if ((*buff))
			(*buff) = ft_strjoin((*buff), (*tmp)->next->value);
		else
			(*buff) = ft_strjoin((*tmp)->value, (*tmp)->next->value);
		(*tmp) = (*tmp)->next;
	}
	else if (verify_is_word_type((*tmp)))
	{
		if ((*buff) != NULL)
		{
			head->file_name = ft_strdup((*buff));
			free((*buff));
			(*buff) = NULL;
		}
		else
			head->file_name = ft_strdup((*tmp)->value);
		(*tmp) = (*tmp)->next;
		return (1);
	}
	return (0);
}

t_redir	*get_redir_list(t_tokens **list)
{
	t_redir		*head;
	t_tokens	*tmp;
	char		*buff;

	buff = NULL;
	head = creat_redir_node(NULL, (*list)->type);
	if (!head)
		return (NULL);
	tmp = (*list)->next;
	while (tmp && verify_is_word_type(tmp) && get_redir_list_helper(&tmp, &buff,
			head))
		;
	return (*list = tmp, head);
}

t_final	*lvlup_ultimate(t_tokens **list, t_final **head)
{
	int	cmd_len;

	cmd_len = calc_cmd_len(*list);
	final_command(head, list, cmd_len);
	return (NULL);
}
