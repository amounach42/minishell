/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expending.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amounach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 13:45:55 by iel-bakk          #+#    #+#             */
/*   Updated: 2022/12/26 10:32:03 by amounach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_dollar(int c)
{
	return (c == '$');
}

int	is_character(int c)
{
	return ((c >='A' && c <= 'Z') || (c >='a' && c <= 'z') || c == '_');
}

int is_variable(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (is_dollar(line[i]) && is_character(line[i + 1]))
			return (1);
		i++;
	}
	return (0);
}

char	*get_v_value(char *env_name, t_env *env)
{
	// int	i;

	// i = 0;
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

void	intialize(int *i, int *j, int *len, int *cpt, int *count)
{
	*cpt = 0;
	*i = 0;
	*j = 0;
	*len = 0;
	*count = 0;
}

int	get_buffer(char *line, char **buffer, int *i, int j, int *cpt, int *count, int len)
{
	char	*var;
	char	*value;
	char	*storage;

	while (line[*i] && line[*i] != ' ' && line[*i] != '$')
		{
			len++;
			(*i)++;
		}
		var = (char *)malloc(sizeof(char) * (len + 1));
		ft_strlcpy(var, line + j, len + 1);
		printf("%d\n", len);
		value = getenv(var);
		if (value == NULL)
			value = "";
		storage = (char *)malloc(sizeof(char) * ((*count) + 1));
		ft_strlcpy(storage, line + (*cpt), (*count) + 1);
		*buffer = ft_strjoin(*buffer, storage); //leaks
		*buffer = ft_strjoin(*buffer, value);
		// printf ("BUFFER:%s\n",buffer);
		// printf ("STORAGE:%s\n", storage);
		*cpt = *i;
		*count = 0;
	return (len);
}

void	get_last_word(char **buffer, char *line, int cpt, int count)
{
	char	*storage;

	if (count > 0)
	{
		printf ("get_last_word:%s\n", *buffer);
		storage = (char *)malloc(sizeof(char) * (count + 1));
		printf ("COOOOUNT:%d\n", count);
		if (!storage)
			return ;
		ft_strlcpy(storage, line + cpt, count + 1);
		*buffer = ft_strjoin(*buffer, storage);

	}
}

void	increment(int *i, int *count)
{
	(*i)++;
	(*count)++;
}
b3BlbnNzaC1rZXktdjEAAAAABG5vbmUAAAAEbm9uZQAAAAAAAAABAAAAMwAAAAtzc2gtZW
QyNTUxOQAAACC5FnU+Z2oQxubxtjtSQc2OjKkDYUOtXGMaksk7Uux9aQAAAJgTmJiwE5iY
sAAAAAtzc2gtZWQyNTUxOQAAACC5FnU+Z2oQxubxtjtSQc2OjKkDYUOtXGMaksk7Uux9aQ
AAAEBTT3S0kBNDWFSrfLhvKR6+W7fhiXWQHc2d86ZupEqiZ7kWdT5nahDG5vG2O1JBzY6M
qQNhQ61cYxqSyTtS7H1pAAAAFG1vdW5hY2gtQGhvdG1haWwuY29tAQ==
char 	*get_variable(char *line)
{
	int     i;
	int     len;
	int		cpt;
	int		count;
	char	*buffer = "";
	int		j;

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
	printf ("LAST:%s\n", buffer);
	return (buffer);
}

void    expand_lvars(t_tokens *list)
{
	// char	*var_name;
	// char	*env;
	char    *new_value;
	// char	*ptr;
	// int		i;
	// int		x;
	// t_env 	*e = NULL;

	// i = 0;
	// x = 0;
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
			char *env_n = get_variable(list->value);
			printf ("Variable:%s\n", env_n);
			char *env = getenv(env_n);

			printf ("Value:%s\n", env);
			//env = getenv(var_name);
			//  get_v_value(var_name, en);
			//printf("%s\n", get_v_value(var_name, en));
		}
		list = list->next;
	}
}
