/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   non_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-bakk < iel-bakk@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 16:38:18 by iel-bakk          #+#    #+#             */
/*   Updated: 2022/12/25 15:33:21 by iel-bakk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "minishell.h"

int compare_to_biultin(char *str)
{
	if (ft_strcmp(str, "pwd") == 0 || ft_strcmp(str, "unset") == 0 || ft_strcmp(str, "export") == 0
		|| ft_strcmp(str, "cd") == 0 || ft_strcmp(str, "exit") == 0 || ft_strcmp(str, "echo") == 0 || ft_strcmp(str, "env") == 0)
		return (1);
	return (0);
}

int check_builtin(char *str, t_env *list)
{
	char    **t;
	int     i;

	(void)list;
	if (!str)
		return (-1);
	if (str[0] == '/') // add a check with access syscall to deterin if that file exists and check before lauching execve if that file is executable.
	{
		if (access((const char *)str, F_OK) != 0)
			return (perror("command not found"),-1);
		t = ft_split(str, '/');
		if (!t)
			return (-1);
		// printf("value %s\n", t[1]);
		i = 0;
		while (t[i + 1])
			i++;
		if (compare_to_biultin(t[i]))
			return (1);
			// printf("it's a builtin command'\n");
		else
			return (2);
			// printf("it's not a builtin command'\n");
	}
	else
	{
		if (compare_to_biultin(str))
			return (1);
			// printf("it's a builtin command'\n");
		else
			return (3);
			// printf("it's not a builtin command'\n");
	}
	return (0);
}



// void    non_builtin(char **param, char **env)
// {
// 	int id;
// 	int	*f;

// 	id = fork();
// 	f = creat_pipe();
// 	if (id == 0)
// 	{
// 		close(f[1]);
// 		dup2(1, f[0]);
// 		execve((const char *)*param, param, env);
// 	}
// 	if (id == 0)
// 	{
		
// 	}
// }

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