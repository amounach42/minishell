/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-bakk < iel-bakk@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 15:02:58 by iel-bakk          #+#    #+#             */
/*   Updated: 2023/01/10 15:04:54 by iel-bakk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expande_variables(t_tokens *list, t_env *env)
{
	char	*new_value;

	while (list)
	{
		if (list->type == VARIABLE)
		{
			new_value = get_variable_new_value(list->value, env);
			if (new_value)
			{
				free(list->value);
				list->value = new_value;
			}
			else
			{
				free(list->value);
				list->value = ft_strdup("");
			}
		}
		else if (list->type == DOUBLE_Q)
			change_value(list, env);
		list = list->next;
	}
}
