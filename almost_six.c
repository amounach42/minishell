/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   almost_six.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-bakk < iel-bakk@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 14:59:44 by iel-bakk          #+#    #+#             */
/*   Updated: 2022/12/26 18:26:02 by iel-bakk         ###   ########.fr       */
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

t_final	*creat_final_node(int tab_len)
{
	t_final	*tmp;

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

int	verify_is_word_type(t_tokens *test)
{
	if (!test)
		return (0);
	if (test->type == WORD || test->type == DOUBLE_Q
		|| test->type == SINGLE_Q || test->type == VARIABLE)
		return (1);
	return (0);
}

int	calc_cmd_len(t_tokens *list)
{
	int			len;

	len = 0;
	while (list)
	{
		if (verify_is_word_type(list) && verify_is_word_type(list->next) && list->space == 0)
			list = list->next;
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
			break ;
	}
	return (len);
}

void	final_commad(t_final **head, t_tokens **list, int len)
{
	t_final		*commad;
	char		*tmp;
	t_tokens	*buff;
	int			i;

	commad = creat_final_node(len);
	tmp = NULL;
	buff = *list;
	i = 0;
	while (verify_is_word_type(buff))
	{
		if (buff->space == 0 && verify_is_word_type(buff->next))
		{
			tmp = ft_strjoin(buff->value, buff->next->value);
			buff->next->value = tmp;
			buff = buff->next;
		}
		else
		{
			commad->str[i] = buff->value;
			i++;
			buff = buff->next;
		}
	}
	commad->str[i] = NULL;
	commad->list = NULL;
	if (*head == NULL)
		*head = commad;
}

//creat a function that will call the lvlup ultimate function

t_final	*lvlup_ultimate(t_tokens *list)
{
	int			cmd_len;
	t_final		*head;
	int			i;

	i = 0;
	head = NULL;
	cmd_len = calc_cmd_len(list);
	final_commad(&head, &list, cmd_len);
	return (head);
}