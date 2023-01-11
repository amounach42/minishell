/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_and_verify.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-bakk < iel-bakk@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 15:09:54 by iel-bakk          #+#    #+#             */
/*   Updated: 2023/01/11 17:10:17 by iel-bakk         ###   ########.fr       */
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
