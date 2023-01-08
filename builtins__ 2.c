/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins__.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amounach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 05:22:09 by amounach          #+#    #+#             */
/*   Updated: 2023/01/08 07:28:47 by amounach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	setup_fds(int fd[2], int last)
{
	dup2(fd[0], 0);
	if (fd[0] != 0)
		close(fd[0]);
	dup2(fd[1], 1);
	if (fd[1] != 1)
	{
		close(fd[1]);
		close(last);
	}
}

int	call_builtin(t_built built, int pip, int fd[2], int last)
{
	int	i;
	int	id;

	i = 0;
	id = 0;
	if (!pip)
		go_builtins(built.cmd, built.list);
	else
	{
		id = fork();
		if (id == 0)
		{
			if (pip)
				setup_fds(fd, last);
			if (!launch_redir(built.cmd->list) && built.cmd->str[i])
				go_builtins(built.cmd, built.list);
			exit(0);
		}
	}
	return (id);
}

void	go_builtins(t_final *cmd, t_env **list)
{
	if (launch_redir(cmd->list))
		return ;
	if (ft_strcmp(cmd->str[0], "pwd") == 0)
		mi_pwd(cmd->str);
	else if (ft_strcmp(cmd->str[0], "echo") == 0)
		mi_echo(cmd->str);
	else if (ft_strcmp(cmd->str[0], "env") == 0)
	{
		if (cmd->str[1] == NULL)
			mi_env(*list);
		else
			write(2, "invalid arguments !!\n", 22);
	}
	else if (ft_strcmp(cmd->str[0], "unset") == 0)
		unset(list, cmd->str);
	else if (ft_strcmp(cmd->str[0], "export") == 0)
		mi_export(cmd->str, list);
	else if (ft_strcmp(cmd->str[0], "exit") == 0)
		ft_exit(cmd->str);
	else if (ft_strcmp(cmd->str[0], "cd") == 0)
		ft_cd(cmd->str, *list);
}

void	export_cases(char **arg, t_env **list)
{
	int		i;
	int		j;
	char	*t;

	i = 0;
	while (arg[++i] != NULL)
	{
		j = -1;
		while (arg[i][++j])
		{
			if (!valid_v_name(arg[i]))
				break ;
			if (arg[i][j] == '=' || arg[i][j] == '+')
			{
				if (arg[i][j] == '+' && arg[i][j + 1] != '=')
					break ;
				t = (char *)malloc(sizeof(char) * j + 1);
				ft_strlcpy(t, arg[i], j + 1);
				modify_envar(t, &arg[i][j], list);
				break ;
			}
		}
		if (arg[i][j] == '\0')
			try_to_creat(arg[i], list);
	}
}

void	push_back_env(t_env **head, t_env *node)
{
	t_env	*last;

	if (!node)
		return ;
	if (!*head)
	{
		*head = node;
		return ;
	}
	last = *head;
	while (last->next)
		last = last->next;
	last->next = node;
}
