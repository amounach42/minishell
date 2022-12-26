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

int mi_cd(char **arg)
{
	if (arg[2])
	{
		// if (arg[3] != NULL)
		// 	write(2, "Invalid argumets !!", 20);
		if (arg[2][0] == '/')
		{
			chdir(arg[2]);
			mi_pwd();
		}
	}
	return (0);
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

int mi_pwd(void)
{
	char *buff;

	buff = NULL;
	buff = getcwd(buff, 0);
	printf("%s\n", buff);
	free(buff);
	return (0);
}

void call_builtin(char **arg, t_env *list)
{
	int i;

	i = 0;
	if (arg[i])
	{
		if (ft_strcmp(arg[0], "pwd") == 0)
		{
			if (arg[1] == NULL)
				mi_pwd();
			else
				write(2, "pwd: too many arguments\n", 25);
		}
		else if (ft_strcmp(arg[0], "echo") == 0)
			mi_echo(arg);
		else if (ft_strcmp(arg[0], "env") == 0)
		{
			if (arg[1] == NULL)
				mi_env(list);
			else
				write(2, "invalid arguments !!\n", 22);
		}
		else if (ft_strcmp(arg[0], "export") == 0)
		{
			mi_export(arg, list);
		}
		// else if (ft_strcmp(arg[1], "cd"))
		// 	mi_cd(arg);
	}
}

void print_export(t_env *list)
{
	while (list)
	{
		printf("declare -x ");
		printf("%s", list->v_name);
		if (list->v_value)
			printf("=%s", list->v_value);
		printf("\n");
		list = list->next;
	}
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
	(void)arg;
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
