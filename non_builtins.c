/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   non_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amounach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 16:38:18 by iel-bakk          #+#    #+#             */
/*   Updated: 2023/01/04 15:43:45 by amounach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	compare_to_biultin(char *str)
{
	if (ft_strcmp(str, "pwd") == 0 || ft_strcmp(str, "unset") == 0
		|| ft_strcmp(str, "export") == 0 || ft_strcmp(str, "cd") == 0
		|| ft_strcmp(str, "exit") == 0 || ft_strcmp(str, "echo") == 0
		|| ft_strcmp(str, "env") == 0)
		return (1);
	return (0);
}

int	check_builtin(char **s, t_env *env)
{
	char	*str;
	char	*tmp;

	str = *s;
	if (!str)
		return (-1);
	if (str[0] == '/')
	{
		if (access((const char *)str, F_OK) != 0)
			return (perror("command not found"), -1);
		return (2);
	}
	else
	{
		if (compare_to_biultin(str))
			return (1);
		else
		{
			tmp = get_cmd_path(str, env);
			if (tmp)
			{
				s[0] = tmp;
			}
			return (2);
		}
	}
	return (0);
}

int	*creat_pipe(void)
{
	int	*fd;

	fd = (int *)malloc(sizeof(int) * 2);
	if (!fd)
		return (NULL);
	if (pipe(fd) == -1)
		return (free(fd), NULL);
	return (fd);
}

int	exec_cmd(t_final *t, char **env, int fd[2])
{
	int pid;

	pid = fork();
	if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
		if (fd[1] != -1)
		{
			dup2(fd[1], 1);
			close(fd[1]);
		}
		if (fd[0] != -1)
		{
			dup2(fd[0], 0);
			close(fd[0]);
		}
		if (launch_redir(t->list))
			exit(0);
		execve(t->str[0], t->str, env);
		write(2, "command not found\n", 18);
		exit(127);
	}
	ft_free(env);
	return (pid);
}