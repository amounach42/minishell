/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   almost_six.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-bakk < iel-bakk@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 14:59:44 by iel-bakk          #+#    #+#             */
/*   Updated: 2023/01/11 17:16:47 by iel-bakk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			printf("%s\n", head->file_name);
		}
		else
			head->file_name = ft_strdup((*tmp)->value);
		(*tmp) = (*tmp)->next;
		return (0);
	}
	return (1);
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
	*list = tmp;
	return (head);
}
