/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amounach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 13:45:55 by iel-bakk          #+#    #+#             */
/*   Updated: 2023/01/04 19:43:45 by amounach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_status(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '?')
	{
		return (ft_itoa(g_tools.status_sign));
	}
	return (NULL);
}

char	*get_env_value(char *env_name, t_env *env)
{
	while (env)
	{
		if (!ft_strcmp(env_name, env->v_name))
			return (env->v_value);
		env = env->next;
	}
	return (NULL);
}

void	change_value(t_tokens *token, t_env *env)
{
	token->value = get_variable(token->value, env);
}

char	*get_variable_new_value(char *str, t_env *env)
{
	int		i;
	char	*tmp;

	i = -1;
	tmp = NULL;
	if (check_status(str))
		return (check_status(str));
	while (str[++i])
	{
		if (!is_alpha_num(str[i]))
			break ;
	}
	if (i)
	{
		tmp = (char *)malloc(sizeof(char) * i + 1);
		if (!tmp)
			return (NULL);
		if (str[i] && !is_alpha_num(str[i]))
		{
			ft_strlcpy(tmp, str, i + 1);
			return (ft_strjoin(get_env_value(tmp, env), str + i));
		}
		else
			return (ft_strdup(get_env_value(str, env)));
	}
	return (tmp);
}

void	expande_variables(t_tokens *list, t_env *env)
{
	char	*new_value;

	while (list)
	{
		if (list->type == VARIABLE)
		{
			new_value = get_variable_new_value(list->value, env);
			if (list->value)
				free(list->value);
			if (new_value)
				list->value = ft_strdup(new_value);
			else
				list->value = ft_strdup("");
		}
		else if (list->type == DOUBLE_Q)
			change_value(list, env);
		list = list->next;
	}
}
