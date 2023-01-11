/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variables.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-bakk < iel-bakk@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 14:33:30 by iel-bakk          #+#    #+#             */
/*   Updated: 2023/01/11 13:29:41 by iel-bakk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_v_name(char *str)
{
	int		i;
	int		len;
	char	*tmp;

	len = 0;
	i = 0;
	while (str[i + len] && str[i + len] != '=')
		len++;
	tmp = (char *)malloc(sizeof(char) * len + 1);
	if (!tmp)
		return (0);
	if (!ft_strlcpy(tmp, str, len + 1))
		return (ft_strdup(""));
	return (tmp);
}

t_env	*creat_env_node(char *v_name)
{
	t_env	*tmp;
	char	cwd[1024];

	getcwd(cwd, 1024);
	tmp = (t_env *)malloc(sizeof(t_env));
	if (!tmp)
		return (NULL);
	tmp->next = NULL;
	if (ft_strlen(v_name) == 0)
	{
		tmp->v_name = ft_strdup("PWD");
		tmp->v_value = ft_strdup(cwd);
	}
	else
	{
		tmp->v_name = v_name;
		tmp->v_value = ft_strdup(getenv(v_name));
	}
	return (tmp);
}

t_env	*creat_env_list(char **env)
{
	int		i;
	t_env	*head;
	t_env	*tmp;

	i = 0;
	if (!*env)
	{
		head = creat_env_node("");
		return (head);
	}
	head = creat_env_node(get_v_name(env[i]));
	if (!head)
		return (NULL);
	tmp = head;
	while (env[++i])
	{
		tmp->next = creat_env_node(get_v_name(env[i]));
		if (!tmp->next)
			return (NULL);
		tmp = tmp->next;
	}
	return (head);
}

void	delete_env_node(t_env **to_delete)
{
	t_env	*tmp;

	tmp = *to_delete;
	if (tmp && tmp->v_name)
	{
		free(tmp->v_name);
		tmp->v_name = NULL;
	}
	if (tmp && tmp->v_value)
	{
		free(tmp->v_value);
		tmp->v_value = NULL;
	}
	tmp->next = NULL;
	free(tmp);
	*to_delete = NULL;
}

void	delete_env_list(t_env **head)
{
	t_env	*tmp;
	t_env	*next;

	tmp = *head;
	while (tmp)
	{
		next = tmp->next;
		if (tmp->v_name)
			free(tmp->v_name);
		tmp->v_value = NULL;
		free(tmp);
		tmp = next;
	}
	*head = NULL;
}
