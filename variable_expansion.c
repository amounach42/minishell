/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amounach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 16:18:49 by amounach          #+#    #+#             */
/*   Updated: 2023/01/04 19:46:56 by amounach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	intialize(t_params *params)
{
	params->cpt = 0;
	params->i = 0;
	params->j = 0;
	params->len = 0;
	params->count = 0;
}

int	get_buffer(t_params *params, t_env *env)
{
	char	*var;
	char	*value;
	char	*storage;

	while (params->line[params->i] && is_alpha_num(params->line[params->i])
		&& params->line[params->i] != '$')
	{
		params->len++;
		(params->i)++;
	}
	var = (char *)malloc((sizeof(char) * (params->len + 1)));
	ft_strlcpy(var, params->line + params->j, params->len + 1);
	value = get_env_value(var, env);
	if (value == NULL)
		value = "";
	storage = (char *)malloc((sizeof(char) * ((params->count) + 1)));
	ft_strlcpy(storage, params->line + (params->cpt), (params->count) + 1);
	params->buffer = ft_strjoin(params->buffer, storage);
	params->buffer = ft_strjoin(params->buffer, value);
	params->cpt = params->i;
	params->count = 0;
	return (params->len);
}

void	get_last_word(t_params *params)
{
	char	*storage;

	if (params->count > 0)
	{
		storage = (char *)malloc((sizeof(char) * (params->count + 1)));
		if (!storage)
			return ;
		ft_strlcpy(storage, params->line + params->cpt, params->count + 1);
		params->buffer = ft_strjoin(params->buffer, storage);
	}
}

int	increment(t_params *params)
{
	(params->i)++;
	(params->count)++;
	return (0);
}

char	*get_variable(char *line, t_env *env)
{
	t_params	param;
	char		*status;

	param.line = line;
	param.buffer = ft_strdup("");
	intialize(&param);
	while (param.line[param.i])
	{
		if (!is_dollar(param.line[param.i]) && !increment(&param))
			continue ;
		status = check_status(&line[param.i + 1]);
		if (status)
		{
			expand_status(&param, status);
			continue ;
		}
		param.i++;
		param.j = param.i;
		param.len = 0;
		get_buffer(&param, env);
	}
	return (get_last_word(&param), param.buffer);
}
