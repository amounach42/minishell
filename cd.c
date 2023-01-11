/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amounach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 12:24:45 by amounach          #+#    #+#             */
/*   Updated: 2023/01/08 10:49:18 by amounach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_arg(char **str)
{
	int	i;

	i = 0;
	if (!*str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

void	change_dir(char *old_pwd, t_env *list)
{
	char	cwd[1024];
	t_env	*tmp;

	tmp = list;
	getcwd(cwd, 1024);
	while (tmp)
	{
		if (!ft_strcmp(tmp->v_name, "PWD"))
		{
			free(tmp->v_value);
			tmp->v_value = ft_strdup(cwd);
		}
		if (!ft_strcmp(tmp->v_name, "OLDPWD"))
		{
			free(tmp->v_value);
			tmp->v_value = ft_strdup(old_pwd);
		}
		tmp = tmp->next;
	}
}

void	check_cd_tilda(char **arg, t_env *list)
{
	char	*old;
	char	cwd[1024];

	old = get_env_value("PWD", list);
	if (arg[0][1])
	{
		if (chdir(ft_strjoin(getenv("HOME"), &arg[0][1])) != 0)
			perror("");
	}
	else
	{
		chdir(getenv("HOME"));
		change_dir(old, list);
	}
	if (arg[0][0] == '.' && arg[0][1] == '\0')
	{
		getcwd(cwd, 1024);
		if (errno == 2)
			perror("cd: error retrieving current directory: \
					getcwd: cannot access parent directories");
	}
}

void	ft_cd(char **arg, t_env *list)
{
	int		count;
	char	*old;

	arg++;
	count = count_arg(arg);
	old = get_env_value("PWD", list);
	if (count > 1)
		ft_putstr_fd(2, "bash: No such file or directory\n");
	if (count == 0)
	{
		chdir(getenv("HOME"));
		change_dir(old, list);
	}
	else
	{
		if (arg[0][0] == '~')
			check_cd_tilda(arg, list);
		else if (chdir(*arg) != 0)
		{
			perror("");
		}
		change_dir(old, list);
	}
}
