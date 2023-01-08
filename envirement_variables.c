/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envirement_variables.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amounach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 05:27:34 by amounach          #+#    #+#             */
/*   Updated: 2023/01/08 05:29:00 by amounach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	delete_onev(t_env **head, t_env *to_d)
{
	t_env	*tmp;

	tmp = *head;
	if (!to_d)
		return ;
	if (*head == to_d)
	{
		*head = tmp->next;
		delete_env_node(&to_d);
		return ;
	}
	while (tmp->next)
	{
		if (tmp->next == to_d)
		{
			tmp->next = tmp->next->next;
			delete_env_node(&to_d);
			return ;
		}
		tmp = tmp->next;
	}
}

int	valid_v_name(char *str)
{
	int	i;

	i = 0;
	if (!str[i])
	{
		perror("Invalid identifier");
		return (0);
	}
	while (str[i])
	{
		if (str[i] == '+' && i > 0 && str[i + 1] == '=' && str[i + 2])
			return (1);
		else if (str[i] == '=' && i > 0)
			return (1);
		else if (!only_char(str[i]))
		{
			perror("Invalid identifier");
			return (0);
		}
		i++;
	}
	return (1);
}

void	try_to_creat(char *new, t_env **list)
{
	t_env	*buff;

	buff = *list;
	while (buff)
	{
		if (ft_strcmp((buff)->v_name, new) == 0)
			break ;
		buff = (buff)->next;
	}
	if (buff == NULL)
		push_back_env(list, creat_env_node(ft_strdup(new)));
}

void	modify_envar(char *name, char *op_value, t_env **list)
{
	char	*buff;
	t_env	*last;

	buff = NULL;
	last = *list;
	last = mitirix_to_env(name, op_value, last, buff);
	if (last == NULL)
	{
		last = *list;
		while (last->next)
			last = last->next;
		last->next = creat_env_node(ft_strdup(name));
		modify_envar(name, op_value, list);
	}
	else
		free(name);
}
