/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expending.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-bakk < iel-bakk@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 13:45:55 by iel-bakk          #+#    #+#             */
/*   Updated: 2023/01/01 14:58:46 by iel-bakk         ###   ########.fr       */
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

void intialize(int *i, int *j, int *len, int *cpt, int *count)
{
	*cpt = 0;
	*i = 0;
	*j = 0;
	*len = 0;
	*count = 0;
}
// int alpha_numeric(int c)
// {
// 	return ((c >= 'a' && c <= 'z')
// 		|| (c >= 'A' && c <= 'Z') 
// 			|| (c >= '0' && c <= '9'));
// }

int get_buffer(char *line, char **buffer, int *i, int j, int *cpt, int *count, int len, t_env *env)
{
	char *var;
	char *value;
	char *storage;

	while (line[*i] && m_alnum(line[*i]) && line[*i] != '$')
	{
		len++;
		(*i)++;
	}
	var = (char *)malloc((sizeof(char) * (len + 1)));
	ft_strlcpy(var, line + j, len + 1);
	value = get_env_value(var, env);//change this part
	if (value == NULL)
		value = "";
	storage = (char *)malloc((sizeof(char) * ((*count) + 1)));
	ft_strlcpy(storage, line + (*cpt), (*count) + 1);
	*buffer = ft_strjoin(*buffer, storage); // leaks
	*buffer = ft_strjoin(*buffer, value);
	*cpt = *i;
	*count = 0;
	return (len);
}

void get_last_word(char **buffer, char *line, int cpt, int count)
{
	char *storage;

	if (count > 0)
	{
		storage = (char *)malloc((sizeof(char) * (count + 1)));
		if (!storage)
			return;
		ft_strlcpy(storage, line + cpt, count + 1);
		*buffer = ft_strjoin(*buffer, storage);
	}
}

void increment(int *i, int *count)
{
	(*i)++;
	(*count)++;
}

char *get_variable(char *line, t_env *env)
{
	int i;
	int len;
	int cpt;
	int count;
	char *buffer = "";
	int j;

	intialize(&i, &j, &len, &cpt, &count);
	while (line[i])
	{
		if (is_dollar(line[i]))
		{
			i++;
			j = i;
			len = 0;
			get_buffer(line, &buffer, &i, j, &cpt, &count, len, env);
		}
		else
			increment(&i, &count);
	}
	get_last_word(&buffer, line, cpt, count);
	return (buffer);
}

void change_value(t_tokens *token, t_env *env)
{
	token->value = get_variable(token->value, env);
}

// char	*getmi_env(char *str)
// {
// 	int	i;

// 	i = 0;
// 	if (!str)
// 		return (NULL);
// 	while (str[i])
// 	{
// 		if (str[i])
// 	}
// }


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