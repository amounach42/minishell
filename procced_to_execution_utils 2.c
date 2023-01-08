/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proced_to_execution_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amounach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 04:38:54 by amounach          #+#    #+#             */
/*   Updated: 2023/01/08 04:39:27 by amounach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	super_free(char **doubl, char *one)
{
	ft_free(doubl);
	free(one);
	return (0);
}

char	*test_paths(char **paths, char *cmd)
{
	int		i;
	char	*tmp;
	char	*buff;

	i = 0;
	while (paths[i])
	{
		buff = ft_strjoin(paths[i], "/");
		tmp = ft_strjoin(buff, cmd);
		free(buff);
		if (access(tmp, F_OK) == 0)
		{
			if (access(tmp, X_OK) == 0)
				return (super_free(paths, cmd), tmp);
			else
				return (super_free(paths, tmp), exit(126), write(2,
						"Permission Denied\n", 18), NULL);
		}
		else
			free(tmp);
		i++;
	}
	ft_free(paths);
	return (NULL);
}

char	*get_cmd_path(char *str, t_env *env)
{
	char	*path;
	char	*tmp;

	tmp = NULL;
	path = get_env_value("PATH", env);
	if (!path)
		return (perror("error"), NULL);
	tmp = test_paths(ft_split(path, ':'), str);
	return (tmp);
}
