/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amounach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 21:47:39 by amounach          #+#    #+#             */
/*   Updated: 2023/01/08 05:31:12 by amounach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_n_option(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-')
		i++;
	else
		return (0);
	while (str[i] == 'n')
		i++;
	return (str[i] == '\0');
}

void	echo_print(int fd, char *str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
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

void	print_export(t_env *list)
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

char	*join_and_free(char *s1, char *s2)
{
	char	*ret;

	ret = ft_strjoin(s1, s2);
	free(s1);
	return (ret);
}

t_env	*mitirix_to_env(char *name, char *op_value, t_env *last, char *buff)
{
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
					write(2, "Error\n", 6);
			}
			else if (*op_value == '=')
			{
				free(last->v_value);
				last->v_value = ft_strdup(op_value + 1);
			}
			break ;
		}
		last = last->next;
	}
	return (last);
}
