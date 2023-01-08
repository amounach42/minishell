/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   procced_to_execution.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amounach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 17:04:27 by iel-bakk          #+#    #+#             */
/*   Updated: 2023/01/08 07:32:25 by amounach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_exit_status_and_wait(int pid)
{
	int	status;

	while (waitpid(pid, &status, 0) != -1)
		;
	if (WIFEXITED(status))
		g_tools.status_sign = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		if (status == SIGINT)
			printf("\n");
		if (status == SIGQUIT)
			printf("Quit : 3\n");
		g_tools.status_sign = 128 + WTERMSIG(status);
	}
	while (waitpid(-1, NULL, 0) != -1)
		;
}

int	exec_command_helper(t_final *t, int *last, t_env **env, int cmd_fd[2])
{
	int	pid;
	int	fd[2];

	while (t)
	{
		cmd_fd[0] = *last;
		if (t->next)
		{
			pipe(fd);
			cmd_fd[1] = fd[1];
			*last = fd[0];
		}
		else
			cmd_fd[1] = -1;
		pid = execute(cmd_fd, env, t, *last);
		close(cmd_fd[0]);
		close(cmd_fd[1]);
		t = t->next;
	}
	return (pid);
}

void	exec_command(t_final *t, t_env **env)
{
	int	cmd_fd[2];
	int	pid;
	int	last;
	int	backup[2];

	last = -1;
	cmd_fd[0] = -1;
	g_tools.status_sign = 0;
	if (!t)
		return ;
	backup[0] = dup(0);
	backup[1] = dup(1);
	if (t->next == NULL && check_builtin(t->str, *env) == 1)
		go_builtins(t, env);
	else
	{
		pid = exec_command_helper(t, &last, env, cmd_fd);
		set_exit_status_and_wait(pid);
	}
	dup2(backup[1], 1);
	dup2(backup[0], 0);
	close(backup[0]);
	close(backup[1]);
}

int	execute(int fd[], t_env **env, t_final *t, int last)
{
	int		check;
	int		pid;
	t_built	built;

	pid = 0;
	built.cmd = t;
	built.list = env;
	check = check_builtin(t->str, *env);
	if (check == 1)
		pid = call_builtin(built, 1, fd, last);
	else if (check == 2)
		pid = exec_cmd(t, convert_from_env_to_tb(*env), fd, last);
	return (pid);
}

char	**convert_from_env_to_tb(t_env *env)
{
	int		len;
	int		i;
	t_env	*tmp;
	char	**str;
	char	*buff;

	len = 0;
	i = 0;
	tmp = env;
	while (tmp)
	{
		len++;
		tmp = tmp->next;
	}
	str = (char **)malloc(sizeof(char *) * (len + 1));
	if (!str)
		return (perror("error"), NULL);
	while (i < len)
	{
		buff = ft_strjoin(env->v_name, "=");
		str[i++] = ft_strjoin(buff, env->v_value);
		free(buff);
		env = env->next;
	}
	return (str[i] = NULL, str);
}
