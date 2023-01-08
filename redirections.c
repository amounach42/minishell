/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amounach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 17:44:56 by iel-bakk          #+#    #+#             */
/*   Updated: 2023/01/08 07:22:59 by amounach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	launch_redirection_output(t_redir **list, int fd)
{
	fd = open((*list)->file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		return (perror((*list)->file_name), 1);
	dup2(fd, 1);
	(*list) = (*list)->next;
	close(fd);
	return (0);
}

int	launch_redirection_input(t_redir **list, int fd)
{
	fd = open((*list)->file_name, O_RDONLY, 0644);
	if (fd < 0)
		return (perror((*list)->file_name), 1);
	dup2(fd, 0);
	(*list) = (*list)->next;
	close(fd);
	return (0);
}

int	launch_append(t_redir **list, int fd)
{
	fd = open((*list)->file_name, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd < 0)
		return (perror((*list)->file_name), 1);
	dup2(fd, 1);
	(*list) = (*list)->next;
	close(fd);
	return (0);
}

int	launch_heredoc(t_redir **list, int fd)
{
	fd = open((*list)->file_name, O_RDONLY, 0644);
	if (fd < 0)
		return (perror((*list)->file_name), 1);
	dup2(fd, 0);
	unlink((*list)->file_name);
	(*list) = (*list)->next;
	close(fd);
	return (0);
}

int	launch_redir(t_redir *list)
{
	int	fd;

	fd = 0;
	while (list)
	{
		if (list && list->type == RE_OUTPUT)
			launch_redirection_output(&list, fd);
		else if (list && list->type == APPEND)
			launch_append(&list, fd);
		else if (list && list->type == RE_INPUT)
			launch_redirection_input(&list, fd);
		else if (list && list->type == HEREDOC)
			launch_heredoc(&list, fd);
		else if (list && (list->type != APPEND || list->type != RE_OUTPUT
				|| list->type != RE_INPUT || list->type != HEREDOC))
			break ;
	}
	return (0);
}
