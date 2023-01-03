/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   procced_to_execution.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-bakk < iel-bakk@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 17:04:27 by iel-bakk          #+#    #+#             */
/*   Updated: 2023/01/01 19:04:25 by iel-bakk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *test_paths(char **paths, char *cmd)
{
	int i;
	char *tmp;
	char *buff;

	i = 0;
	while (paths[i])
	{
		buff = ft_strjoin(paths[i], "/");
		tmp = ft_strjoin(buff, cmd);
		free(buff);
		if (access(tmp, F_OK) == 0)
		{
			if (access(tmp, X_OK) == 0)
				return (tmp);
			else
				return (write(2, "Permission Denied\n", 18), NULL);
		}
		i++;
	}
	ft_free(paths);
	return (NULL);
}

char *get_cmd_path(char *str, t_env *env)
{
	char *path;
	char *tmp;

	tmp = NULL;
	path = get_env_value("PATH", env);
	if (!path)
		return (perror("error"), NULL);
	tmp = test_paths(ft_split(path, ':'), str);
	return (tmp);
}

void exec_command(t_final *t, t_env *env)
{
	int fd[2];
	int cmd_fd[2];
	int pid;
	int last;
	int	backup[2];

	last = -1;
	cmd_fd[0] = -1;
	if (!t)
		return ;
	backup[0] = dup(0);
	backup[1] = dup(1);
	if (t->next == NULL && check_builtin(t->str, env) == 1)
		go_builtins(t, env);
	else
	{
	while (t)
	{
		cmd_fd[0] = last;
		if (t->next)
		{
			pipe(fd);
			cmd_fd[1] = fd[1];
			last = fd[0];
		}
		else
			cmd_fd[1] = -1;
		pid = execute(cmd_fd, env, t);
		close(cmd_fd[0]);
		close(cmd_fd[1]);
		t = t->next;
	}
	waitpid(pid, NULL, 0);
	}
	dup2(backup[1], 1);
	dup2(backup[0], 0);
	close(backup[0]);
	close(backup[1]);
}

int execute(int fd[], t_env *env, t_final *t)
{
	int check;
	int pid;

	pid = 0;
	check = check_builtin(t->str, env);

	if (check == 1)
		pid = call_builtin(t, env, 1, fd);
	else if (check == 2)
		pid = exec_cmd(t, convert_from_env_to_tb(env), fd);
	return (pid);
}

// this function will transform the env linked list to a char **
// and pass it to exec_cmd, don't forget to free the ** after using it
char **convert_from_env_to_tb(t_env *env)
{
	int len;
	int i;
	t_env *tmp;
	char **str;
	char *buff;

	len = 0;
	i = 0;
	tmp = env;
	while (tmp)
	{
		len++;
		tmp = tmp->next;
	}
	str = (char **)malloc(sizeof(char *) * len + 1);
	if (!str)
		return (perror("error"), NULL);
	while (i < len)
	{
		buff = ft_strjoin(env->v_name, "=");
		str[i] = ft_strjoin(buff, env->v_value);
		free(buff);
		i++;
		env = env->next;
	}
	str[i] = NULL;
	return (str);
}