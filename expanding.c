/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-bakk < iel-bakk@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 13:45:55 by iel-bakk          #+#    #+#             */
/*   Updated: 2023/01/10 15:04:02 by iel-bakk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*get_env_value_(char *env_name, t_env *env)
{
	while (env)
	{
		if (!ft_strcmp(env_name, env->v_name))
			return (free(env_name), env->v_value);
		env = env->next;
	}
	return (NULL);
}

void	change_value(t_tokens *token, t_env *env)
{
	char	*tmp;

	tmp = token->value;
	token->value = get_variable(tmp, env);
	free(tmp);
}

char	*check_and_allocate(char *str, t_env *env, int *i)
{
	char	*tmp;
	char	*buff;

	tmp = (char *)malloc(sizeof(char) * ((*i) + 1));
	if (!tmp)
		return (NULL);
	ft_strlcpy(tmp, str, (*i) + 1);
	buff = get_env_value(tmp, env);
	return (free(tmp), join_and_free(buff, str + (*i)));
}

char	*get_variable_new_value(char *str, t_env *env)
{
	int		i;
	char	*tmp;

	i = -1;
	tmp = check_status(str);
	if (tmp)
		return (tmp);
	tmp = NULL;
	while (str[++i])
		if (!is_alpha_num(str[i]))
			break ;
	if (i)
	{
		if (str[i] && !is_alpha_num(str[i]))
			check_and_allocate(str, env, &i);
		else
			return (ft_strdup(get_env_value(str, env)));
	}
	return (tmp);
}
