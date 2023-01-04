/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amounach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 00:37:32 by amounach          #+#    #+#             */
/*   Updated: 2023/01/04 15:37:07 by amounach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	file_is_exists(const char *file_name)
{
	return (!access(file_name, F_OK));
}

char	*change_file_name(char *file_name, int *idx)
{
	if (file_is_exists(ft_strjoin("/tmp/", file_name)))
		return (change_file_name(ft_strjoin(file_name, ft_itoa((*idx)++)),
				idx));
	return (ft_strjoin("/tmp/", file_name));
}

void	check_eof(char **value, int type)
{
	char	*line;
	int		fd;
	char	*buff;
	int		idx;

	idx = 0;
	if (type == VARIABLE)
		*value = ft_strjoin("$", *value);
	line = ft_strdup("");
	buff = ft_strdup("");
	while (1)
	{
		line = readline(">");
		if (!global)
			return ;
		if (!line || !ft_strcmp(*value, line))
			break ;
		else
			buff = ft_strjoin(buff, ft_strjoin(line, "\n"));
	}
	*value = change_file_name("heredoc", &idx);
	fd = open(*value, O_CREAT | O_RDWR | O_TRUNC, 0644);
	ft_putstr_fd(fd, buff);
	close(fd);
}

void	open_heredoc(t_tokens *token)
{
	t_tokens	*tmp;

	tmp = token;
	while (tmp && global)
	{
		if (tmp->type == HEREDOC)
		{
			if (tmp->next->type == WSPACE)
				check_eof(&tmp->next->next->value, tmp->next->next->type);
			else
				check_eof(&tmp->next->value, tmp->next->type);
		}
		tmp = tmp->next;
	}
}
