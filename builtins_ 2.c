/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amounach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 05:29:55 by amounach          #+#    #+#             */
/*   Updated: 2023/01/08 05:50:33 by amounach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	mi_echo(char **arg)
{
	int	i;
	int	nl;

	i = 1;
	nl = 0;
	if (arg[i])
	{
		nl = check_n_option(arg[i]);
		if (nl)
			i++;
	}
	while (arg[i])
	{
		echo_print(1, arg[i]);
		if (arg[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (!nl)
		write(1, "\n", 1);
	return (0);
}

int	mi_pwd(char **str)
{
	char	buff[PATH_MAX];

	if (str[1] == NULL)
	{
		getcwd(buff, PATH_MAX);
		printf("%s\n", buff);
	}
	else
		write(2, "pwd: too many arguments\n", 25);
	return (0);
}

void	ft_exit(char **str)
{
	write(1, "exit\n", 5);
	if (str[1])
	{
		if (check_if_num(str[1]) && str[2])
		{
			write(2, "bash: exit: too many arguments\n", 31);
			return ;
		}
		else if (check_if_num(str[1]))
			exit(ft_atoi(str[1]));
		else
		{
			write(2, "bash: exit : numeric argument required\n", 40);
			exit(-1);
		}
	}
	exit(0);
}

void	mi_export(char **arg, t_env **list)
{
	if (arg[1])
		export_cases(arg, list);
	else
		print_export(*list);
}

void	mi_env(t_env *list)
{
	while (list)
	{
		if (list->v_value)
		{
			ft_putstr_fd(1, list->v_name);
			write(1, "=", 1);
			ft_putstr_fd(1, list->v_value);
			write(1, "\n", 1);
		}
		list = list->next;
	}
}
