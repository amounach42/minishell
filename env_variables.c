/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variables.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amounach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 14:33:30 by iel-bakk          #+#    #+#             */
/*   Updated: 2022/12/30 21:48:51 by amounach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    *get_v_name(char *str)
{
	int     i;
	int     len;
	char    *tmp;

	len = 0;
	i = 0;
	while (str[i + len] && str[i + len] != '=')
		len++;
	tmp = (char *)malloc(sizeof(char) * len + 1);
	if (!tmp)
		return (0);
	if (!ft_strlcpy(tmp , str, len + 1))
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
		tmp->v_name = "PWD";
		tmp->v_value = ft_strdup(cwd);
	}
	else
	{
		tmp->v_name = v_name;
		tmp->v_value = getenv(v_name);
	}
	return (tmp);
}
// creat a fucntion that loops over the **env and creats the t_env nodes and fills theme up.
// don't forget to protect what get_v_name returns to avoid problemes and find a way to store the size of the list
// maybe on another struct wich will diffenetly be the struct we will be using during the execution
// it's not a necessity but just think about it you never know ou might needed it.

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
	if (tmp->v_name)
	{
		free(tmp->v_name);
		tmp->v_name = NULL;
	}
	if (tmp->v_value)
		tmp->v_value = NULL;
	tmp->next =NULL;
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
		// delete_env_node(&tmp);
		tmp = next;
	}
	*head = NULL;
}

void	delete_onev(t_env **head, t_env *to_d)
{
	t_env	*tmp;

	tmp = *head;
	if (!to_d)
		return ;
	if (tmp == to_d)
	{
		*head = tmp->next;
		delete_env_node(&tmp);
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
