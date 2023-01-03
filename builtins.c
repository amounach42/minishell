#include "minishell.h"

void ft_putstr_fd(int fd, char *str)
{
	int i;

	i = 0;
	while (str[i])
		i += write(fd, &str[i], 1);
}

int check_n_option(char *str)
{
	int i;

	i = 0;
	if (str[i] == '-')
		i++;
	else
		return (0);
	while (str[i] == 'n')
		i++;
	return (str[i] == '\0');
}

int ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	if (!s1)
		return (1);
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

void echo_print(int fd, char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
		{
			write(fd, "\n", 1);
			i++;
		}
		else
			i += write(fd, &str[i], 1);
	}
}

int mi_echo(char **arg)
{
	int i;
	int nl;

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

#include <limits.h>

int	mi_pwd(void)
{
	char	buff[PATH_MAX];
	
	getcwd(buff, PATH_MAX);
	printf("%s\n", buff);
	return (0);
}

int call_builtin(t_final	*cmd, t_env *list, int pip, int fd[2])
{
	int i;
	int id;

	i = 0;
	id = 0;
	if (!pip)
		go_builtins(cmd, list);
	else
	{
		id = fork();
		if (id == 0)
		{
			if (pip)
			{
				if (fd[0] != 0)
				{
					dup2(fd[0], 0);
					close(fd[0]);
				}
				if (fd[1] != 1)
				{
					dup2(fd[1], 1);
					close(fd[1]);
				}
			}
			launch_redir(cmd->list);
			if (cmd->str[i])
				go_builtins(cmd, list);
			exit(0);
		}
		waitpid(id, NULL, 0);
	}
	return (id);
}


void	go_builtins(t_final *cmd, t_env *list)
{
	launch_redir(cmd->list);
	if (ft_strcmp(cmd->str[0], "pwd") == 0)
	{
		if (cmd->str[1] == NULL)
			mi_pwd();
		else
			write(2, "pwd: too many arguments\n", 25);
	}
	else if (ft_strcmp(cmd->str[0], "echo") == 0)
		mi_echo(cmd->str);
	else if (ft_strcmp(cmd->str[0], "env") == 0)
	{
		if (cmd->str[1] == NULL)
			mi_env(list);
		else
			write(2, "invalid arguments !!\n", 22);
	}
	else if (ft_strcmp(cmd->str[0], "unset") == 0)
		unset(&list, cmd->str);
	else if (ft_strcmp(cmd->str[0], "export") == 0)
		mi_export(cmd->str, list);
	else if (ft_strcmp(cmd->str[0], "exit") == 0)
		exit(0);
	else if (ft_strcmp(cmd->str[0], "cd") == 0)
		ft_cd(cmd->str, list);
}

void print_export(t_env *list)
{
	while (list)
	{
		printf("declare -x ");
		printf("%s", list->v_name);
		if (list->v_value)
			printf("=\"%s\"", list->v_value);
		printf("\n");
		list = list->next;
	}
}

int only_char(char c)
{
	if (c >= 'a' && c <= 'z')
		return (1);
	else if (c >= 'A' && c <= 'Z')
		return (1);
	else if (c == '_')
		return (1);
	return (0);
}

int valid_v_name(char *str)
{
	int i;

	i = 0;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] == '+' && i > 0 && str[i + 1] == '=' && str[i + 2])
			return (1);
		else if (str[i] == '=' && i > 0)
			return (1);
		else if (!only_char(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void export_cases(char **arg, t_env *list)
{
	int i;
	int j;
	char *t;

	i = 1;
	while (arg[i] != NULL)
	{
		j = 0;
		while (arg[i][j])
		{
			if (!valid_v_name(arg[i]))
			{
				perror("Invalid identifier");
				break;
			}
			if (arg[i][j] == '=' || arg[i][j] == '+')
			{
				if (arg[i][j] == '+' && arg[i][j + 1] != '=')
					break;
				t = (char *)malloc(sizeof(char) * j + 1);
				ft_strlcpy(t, arg[i], j + 1);
				modify_envar(t, &arg[i][j], list);
				break;
			}
			j++;
		}
		if (arg[i][j] == '\0')
			try_to_creat(arg[i], list);
		i++;
	}
}

void try_to_creat(char *new, t_env *list)
{
	t_env *buff;

	buff = list;
	while (list)
	{
		if (ft_strcmp(list->v_name, new) == 0)
			break;
		list = list->next;
	}
	if (list == NULL)
	{
		while (buff->next)
			buff = buff->next;
		buff->next = creat_env_node(new);
	}
}

void modify_envar(char *name, char *op_value, t_env *list)
{
	char *buff;
	t_env *last;

	last = list;
	while (last)
	{
		if (ft_strcmp(name, last->v_name) == 0)
		{
			if (*op_value == '+')
			{
				if (op_value[1] == '=')
				{
					buff = last->v_value;
					last->v_value = ft_strjoin(last->v_value, op_value + 2);
					free(buff);
				}
				else
				{
					write(2, "Error\n", 6);
				}
			}
			else if (*op_value == '=')
			{
				free(last->v_value);
				last->v_value = ft_strdup(op_value + 1);
			}
			break;
		}
		last = last->next;
	}
	if (last == NULL)
	{
		last = list;
		while (last->next)
			last = last->next;
		last->next = creat_env_node(ft_strdup(name));
		modify_envar(name, op_value, list);
	}
	else
		free(name);
}

void mi_export(char **arg, t_env *list)
{
	if (arg[1])
		export_cases(arg, list);
	else
		print_export(list);
}

void mi_env(t_env *list)
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
