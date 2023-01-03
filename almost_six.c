/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   almost_six.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-bakk < iel-bakk@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 14:59:44 by iel-bakk          #+#    #+#             */
/*   Updated: 2023/01/02 18:37:11 by iel-bakk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redir *creat_redir_node(char *file_name, int type)
{
	t_redir *tmp;

	tmp = (t_redir *)malloc(sizeof(t_redir));
	if (!tmp)
		return (NULL);
	tmp->file_name = file_name;
	tmp->type = type;
	tmp->next = NULL;
	return (tmp);
}

t_final *creat_final_node(int tab_len)
{
	t_final *tmp;

	tmp = (t_final *)malloc(sizeof(t_final));
	if (!tmp)
		return (NULL);
	tmp->list = NULL;
	tmp->next = NULL;
	tmp->str = (char **)malloc(sizeof(char *) * tab_len + 1);
	if (!tmp->str)
		return (NULL);
	return (tmp);
}

int verify_is_redir_type(t_tokens *test)
{
	if (test == NULL)
		return (0);
	if (test->type == RE_INPUT || test->type == RE_OUTPUT || test->type == APPEND || test->type == HEREDOC)
		return (1);
	return (0);
}

int verify_is_word_type(t_tokens *test)
{
	if (!test)
		return (0);
	if (test->type == WORD || test->type == DOUBLE_Q || test->type == SINGLE_Q || test->type == VARIABLE)
		return (1);
	return (0);
}

int calc_cmd_len(t_tokens *list)
{
	int len;

	len = 0;
	while (list)
	{
		if (verify_is_word_type(list) && verify_is_word_type(list->next) && list->space == 0)
			list = list->next;
		else if (verify_is_redir_type(list)  && verify_is_word_type(list->next))
		{
			list = list->next;
			list = list->next;
		}
		else if (verify_is_word_type(list) && list->space)
		{
			len++;
			list = list->next;
		}
		else if (verify_is_word_type(list) && (list->next == NULL || !verify_is_word_type(list->next)))
		{
			len++;
			list = list->next;
		}
		else
			break;
	}
	return (len);
}

void add_final_end(t_final **head, t_final *new)
{
	t_final *tmp;

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

void add_redir_end(t_redir **head, t_redir *new)
{
	t_redir *tmp;

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

void final_command(t_final **head, t_tokens **list, int len)
{
	t_final 	*command;
	char 		*tmp;
	t_tokens 	*buff;
	int 		i;

	if (!(*list) || !list)
		return ;
	command = creat_final_node(len);
	if (!command)
		return ;
	tmp = NULL;
	buff = *list;
	i = 0;
	while (1)
	{
		if (!buff)
			break ;
		if (verify_is_redir_type(buff))
		{
			add_redir_end(&command->list, get_redir_list(&buff));
		}
		else if (verify_is_word_type(buff))
		{
			if (buff->space == 0 && buff->next && verify_is_word_type(buff->next))
			{
				if (tmp)
				{
					tmp = ft_strjoin(tmp, buff->next->value);
					buff = buff->next;
				}
				else
				{
					tmp = ft_strjoin(buff->value, buff->next->value);
					buff = buff->next;
				}
			}
			else
			{
				if (tmp)
				{
					command->str[i++] = ft_strdup(tmp);
					free(tmp);
					tmp = NULL;
					buff = buff->next;
				}
				else
				{
					command->str[i++] = ft_strdup(buff->value);
					buff = buff->next;
				}
			}
		}
		else
			break ;
		// if (buff == NULL || buff->type == PIPE)
		// 	break;
		// if (verify_is_word_type(buff))
		// {
		// 	if (buff->space == 0 && verify_is_word_type(buff->next))
		// 	{
		// 		tmp = ft_strjoin(buff->value, buff->next->value);
		// 		buff->next->value = ft_strdup(tmp);
		// 		buff = buff->next;
		// 		free(tmp);
		// 		tmp = NULL;
		// 	}
		// 	else
		// 	{
		// 		if (tmp)
		// 			command->str[i] = tmp;
		// 		else if (buff->value)
		// 			command->str[i] = buff->value;
		// 		i++;
		// 		buff = buff->next;
		// 	}
		// }
		// else if (buff && verify_is_redir_type(buff))
		// 	add_redir_end(&command->list, get_redir_list(&buff));
	}
	command->str[i] = NULL;
	*list = buff;
	add_final_end(head, command);
}

// void	add_redir_to_list(t_tokens **token, t_final *cmd)
// {
// 	t_redir	*last;

// 	if (!cmd)
// 		return ;
// 	if (cmd->list)
// 		last = cmd->list;
// 	else
// 	{
// 		cmd->list = malloc(sizeof(t_redir));
// 		cmd->list->file_name = NULL;
// 		cmd->list->next = NULL;
// 		cmd->list->type = 0;
// 		last = cmd->list;
// 	}
// 	while (last->next)
// 		last = last->next;
// 	last->next = current_redir(token);
// }

t_final *convert_from_tokens_to_final(t_tokens *list)
{
	t_final *head;

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

// t_redir	*current_redir(t_tokens **token)
// {
// 	int			type;
// 	t_tokens	*tmp;
// 	t_redir		*new;
// 	char		*buff;

// 	if (!(token) || !(*token))
// 		return (NULL);
// 	tmp = *token;
// 	buff = NULL;
// 	if (verify_is_redir_type(tmp) && tmp->next)
// 	{
// 		type = tmp->type;
// 		new = malloc(sizeof(t_redir));
// 		if (!new)
// 			return (NULL);
// 		tmp = tmp->next;
// 		while (verify_is_word_type(tmp))
// 		{
// 			if (tmp->space == 0 && tmp->next && verify_is_word_type(tmp->next))
// 			{
// 				if (buff)
// 					buff = ft_strjoin(buff, tmp->next->value);
// 				else
// 					buff = ft_strjoin(tmp->value, tmp->next->value);
// 				tmp = tmp->next;
// 			}
// 			else if (buff)
// 			{
// 				new->file_name = ft_strdup(buff);
// 				tmp = tmp->next;
// 				break ;
// 			}
// 			else
// 			{
// 				new->file_name = ft_strdup(tmp->value);
// 				tmp = tmp->next;
// 				break ;
// 			}
// 		}
// 		*token = tmp;
// 		return (new);
// 	}
// 	return (NULL);
// }

t_redir *get_redir_list(t_tokens **list)
{
	t_redir 	*head;
	t_tokens	*tmp;
	char		*buff;

	buff = NULL;
	tmp = *list;
	head = creat_redir_node(NULL, tmp->type);
	if (!head)
		return (NULL);
	tmp = tmp->next;
	while (tmp && verify_is_word_type(tmp))
	{
		if (tmp->space == 0 && tmp->next && verify_is_word_type(tmp->next))
		{
			if (buff)
				buff = ft_strjoin(buff, tmp->next->value);
			else
				buff = ft_strjoin(tmp->value, tmp->next->value);
			tmp = tmp->next;
		}
		else if (verify_is_word_type(tmp))
		{
			if (buff != NULL)
			{
				head->file_name = ft_strdup(buff);
				free(buff);
				buff = NULL;
			}
			else
				head->file_name = ft_strdup(tmp->value);
			tmp = tmp->next;
			break ;
		}
		else if (!tmp || (verify_is_redir_type(tmp) || tmp->type == PIPE))
			break ;
	}
	*list = tmp;
	return (head);
}

// t_redir *get_redir_list(t_tokens **list)
// {
// 	t_tokens *tmp;
// 	t_redir *head;
// 	char *buff;
// 	int type;

// 	tmp = *list;
// 	head = malloc(sizeof(t_redir));
// 	if (!head)
// 		return (NULL);
// 	head->type = tmp->type;
// 	head->file_name = tmp->next->value;
// 	head->next = NULL;
// 	*list = tmp->next->next;
// 	// if (verify_is_redir_type(tmp))
// 	// {
// 	// 	type = tmp->type;
// 	// 	tmp = tmp->next;
// 	// }
// 	// else
// 	// 	return (NULL);
// 	// head = creat_redir_node(tmp->value, type);
// 	// buff = NULL;
// 	// while (!verify_is_redir_type(tmp) && tmp->type != PIPE)
// 	// {
// 	// 	if (verify_is_word_type(tmp->next) && tmp->space == 0 && buff)
// 	// 	{
// 	// 		buff = ft_strjoin(buff, tmp->next->value);
// 	// 		tmp = tmp->next;
// 	// 	}
// 	// 	else if (verify_is_word_type(tmp) && tmp->space == 0 && verify_is_word_type(tmp->next))
// 	// 	{
// 	// 		buff = ft_strjoin(tmp->value, tmp->next->value);
// 	// 		tmp = tmp->next;
// 	// 	}
// 	// 	if (verify_is_word_type(tmp))
// 	// 	{
// 	// 		if (buff)
// 	// 		{
// 	// 			head->file_name = buff;
// 	// 			free(buff);
// 	// 			buff = NULL;
// 	// 		}
// 	// 		else if (verify_is_word_type(tmp) && verify_is_redir_type(tmp->prev))
// 	// 			head->file_name = tmp->value;
// 	// 		tmp = tmp->next;
// 	// 		break;
// 	// 	}
// 	// }
// 	// *list = tmp;
// 	return (head);
// }


t_final *lvlup_ultimate(t_tokens **list, t_final **head)
{
	int cmd_len;

	cmd_len = calc_cmd_len(*list);
	final_command(head, list, cmd_len);
	return (NULL);
}