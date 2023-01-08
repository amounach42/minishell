/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linkedlist_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amounach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 03:23:35 by amounach          #+#    #+#             */
/*   Updated: 2023/01/03 15:10:12 by amounach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tokens	*new_node(int type, char *value)
{
	t_tokens	*node;

	node = malloc(sizeof(t_tokens));
	if (!node)
		return (NULL);
	node->type = type;
	node->value = value;
	node->next = NULL;
	return (node);
}

void	push_back(t_tokens **head, t_tokens *node)
{
	t_tokens	*last;

	if (!node)
		return ;
	if (!*head)
	{
		*head = node;
		return ;
	}
	last = *head;
	while (last)
		last = last->next;
	last->next = node;
}

void	push_front(t_tokens **head, t_tokens *node)
{
	if (!node)
		return ;
	node->next = *head;
	*head = node;
}

void	display(t_tokens *head)
{
	while (head)
	{
		printf("Type: %d\nValue: %s", head->type, head->value);
		head = head->next;
	}
}
