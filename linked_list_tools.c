/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-bakk < iel-bakk@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 15:14:36 by iel-bakk          #+#    #+#             */
/*   Updated: 2023/01/11 17:24:55 by iel-bakk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

t_final	*lvlup_ultimate(t_tokens **list, t_final **head)
{
	int	cmd_len;

	cmd_len = calc_cmd_len(*list);
	final_command(head, list, cmd_len);
	return (NULL);
}
