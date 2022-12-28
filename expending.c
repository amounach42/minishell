/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expending.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amounach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 13:45:55 by iel-bakk          #+#    #+#             */
/*   Updated: 2022/12/28 17:19:00 by amounach         ###   ########.fr       */
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

char *get_v_value(char *env_name, t_env *env)
{
	while (env)
	{
		if (!ft_strcmp(env_name, env->v_name))
			return (env->v_value);
		else if (ft_strcmp(env_name, env->v_value))
			env = env->next;
		else
			return (0);
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

int alpha_numeric(int c)
{
	return ((c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z') 
			|| (c >= '0' && c <= '9'));
}

int get_buffer(char *line, char **buffer, int *i, int j, int *cpt, int *count, int len)
{
	char *var;
	char *value;
	char *storage;

	while (line[*i] && alpha_numeric(line[*i]) && line[*i] != '$')
	{
		len++;
		(*i)++;
	}
	var = (char *)malloc((sizeof(char) * (len + 1)));
	ft_strlcpy(var, line + j, len + 1);
	value = getenv(var);
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

char *get_variable(char *line)
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
			get_buffer(line, &buffer, &i, j, &cpt, &count, len);
		}
		else
			increment(&i, &count);
	}
	get_last_word(&buffer, line, cpt, count);
	return (buffer);
}

void change_value(t_tokens *token)
{
	token->value = get_variable(token->value);
}

void expand_lvars(t_tokens *list)
{
	char *new_value;

	while (list)
	{
		if (list->type == VARIABLE)
		{
			new_value = getenv(list->value);
			if (list->value)
				free(list->value);
			if (new_value)
				list->value = ft_strdup(new_value);
			else
				list->value = ft_strdup("");
		}
		else if (list->type == DOUBLE_Q)
		{
			get_variable(list->value);
			change_value(list);
			printf("\nNew value:%s\n", list->value);
		}
		list = list->next;
	}
}
