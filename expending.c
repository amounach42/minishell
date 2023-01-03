/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expending.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amounach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 13:45:55 by iel-bakk          #+#    #+#             */
/*   Updated: 2023/01/03 19:32:29 by amounach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_dollar(int c)
{
	return (c == '$');
}

int is_character(int c)
{
	return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '_');
}

int is_variable(char *line)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (is_dollar(line[i]) && is_character(line[i + 1]))
			return (1);
		i++;
	}
	return (0);
}

char *get_env_value(char *env_name, t_env *env)
{
	while (env)
	{
		if (!ft_strcmp(env_name, env->v_name))
			return (env->v_value);
		env = env->next;
	}
	return (NULL);
}

void intialize(t_params *params)
{
	params->cpt = 0;
	params->i = 0;
	params->j = 0;
	params->len = 0;
	params->count = 0;
}

int get_buffer(t_params *params, t_env *env)
{
	char *var;
	char *value;
	char *storage;

	while (params->line[params->i] && m_alnum(params->line[params->i]) && params->line[params->i] != '$')
	{
		params->len++;
		(params->i)++;
	}
	var = (char *)malloc((sizeof(char) * (params->len + 1)));
	ft_strlcpy(var, params->line + params->j, params->len + 1);
	value = get_env_value(var, env);//change this part
	if (value == NULL)
		value = "";
	storage = (char *)malloc((sizeof(char) * ((params->count) + 1)));
	ft_strlcpy(storage, params->line + (params->cpt), (params->count) + 1);
	params->buffer = ft_strjoin(params->buffer, storage); // leaks
	params->buffer = ft_strjoin(params->buffer, value);
	params->cpt = params->i;
	params->count = 0;
	return (params->len);
}

void get_last_word(t_params *params)
{
	char *storage;

	if (params->count > 0)
	{
		storage = (char *)malloc((sizeof(char) * (params->count + 1)));
		if (!storage)
			return;
		ft_strlcpy(storage, params->line + params->cpt, params->count + 1);
		params->buffer = ft_strjoin(params->buffer, storage);
	}
}

void increment(t_params *params)
{
	(params->i)++;
	(params->count)++;
}

char *get_variable(char *line, t_env *env)
{
	t_params param;


	param.line = line;
	param.buffer = ft_strdup("");
	intialize(&param);
	while (param.line[param.i])
	{
		if (is_dollar(param.line[param.i]))
		{
			param.i++;
			param.j = param.i;
			param.len = 0;
			get_buffer(&param, env);
		}
		else
			increment(&param);
	}
	get_last_word(&param);
	return (param.buffer);
}

void change_value(t_tokens *token, t_env *env)
{
	token->value = get_variable(token->value, env);
}

int	m_alnum(char c)
{
	if (c >= 'a' && c <= 'z')
		return (1);
	else if (c >= 'A' && c <= 'Z')
		return (1);
	else if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

char	*get_variable_new_value(char *str, t_env *env)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = NULL;
	while (str[i])
	{
		if (!m_alnum(str[i]))
			break ;
		i++;
	}
	if (i)
	{
		tmp = (char *)malloc(sizeof(char) * i + 1);
		if (!tmp)
			return (NULL);
		if (str[i] && !m_alnum(str[i]))
		{
			ft_strlcpy(tmp, str, i + 1);
			return (ft_strjoin(get_env_value(tmp, env), str + i));
		}
		else
			return (ft_strdup(get_env_value(str, env)));
	}
	return (tmp);
}

void expand_lvars(t_tokens *list, t_env *env)
{
	char *new_value;

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
		{
			get_variable(list->value, env);
			change_value(list, env);
		}
		list = list->next;
	}
}