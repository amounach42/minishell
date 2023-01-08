/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amounach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 00:37:32 by amounach          #+#    #+#             */
/*   Updated: 2023/01/08 08:38:33 by amounach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	file_is_exists(const char *file_name)
{
	return (!access(file_name, F_OK));
}

char	*change_file_name(char *file_name, int *idx)
{
	char	*tmp;
	char	*tmp2;
	char	*tmp_num;

	tmp = ft_strjoin("/tmp/", file_name);
	if (file_is_exists(tmp))
	{
		tmp_num = ft_itoa((*idx)++);
		tmp2 = ft_strjoin(file_name, tmp_num);
		free(file_name);
		free(tmp_num);
		free(tmp);
		return (change_file_name(tmp2, idx));
	}
	else
		free(file_name);
	return (tmp);
}

void	check_eof_helper(int *idx, char **value, int *type, char *buff)
{
	int	fd;

	free(*value);
	*value = change_file_name(ft_strdup("heredoc"), idx);
	*type = WORD;
	fd = open(*value, O_CREAT | O_RDWR | O_TRUNC, 0644);
	ft_putstr_fd(fd, buff);
	free(buff);
	close(fd);
}

void	modify_eof(t_eof *eof)
{
	eof->tmp = ft_strjoin(eof->line, "\n");
	eof->tmp2 = ft_strjoin(eof->buff, eof->tmp);
	free(eof->buff);
	eof->buff = eof->tmp2;
	free(eof->tmp);
}

void	delimiter_variable(t_eof *eof, char **value)
{
	eof->tmp = ft_strjoin("$", *value);
	free(*value);
	*value = ft_strdup(eof->tmp);
	free(eof->tmp);
}

void	check_eof(char **value, int *type)
{
	t_eof	eof;

	eof.idx = 0;
	if (*type == VARIABLE)
		delimiter_variable(&eof, value);
	eof.buff = ft_strdup("");
	while (1)
	{
		eof.line = readline(">");
		if (!g_tools.global)
		{
			free(eof.line);
			return ;
		}
		if (!eof.line || !ft_strcmp(*value, eof.line))
		{
			if (eof.line)
				free(eof.line);
			break ;
		}
		else
			modify_eof(&eof);
		free(eof.line);
	}
	check_eof_helper(&eof.idx, value, type, eof.buff);
}

void	open_heredoc(t_tokens *token)
{
	t_tokens	*tmp;

	tmp = token;
	while (tmp && g_tools.global)
	{
		if (tmp->type == HEREDOC)
		{
			if (tmp->next->type == WSPACE)
				check_eof(&tmp->next->next->value, &tmp->next->next->type);
			else
				check_eof(&tmp->next->value, &tmp->next->type);
		}
		tmp = tmp->next;
	}
}
