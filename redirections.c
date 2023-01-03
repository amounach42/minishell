/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amounach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 17:44:56 by iel-bakk          #+#    #+#             */
/*   Updated: 2023/01/03 13:20:02 by amounach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void launch_redir(t_redir *list)
{
	int fd;

	while (list)
	{
		if (list && list->type == RE_OUTPUT)
		{
			fd = open(list->file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
			if(fd < 0)
			{
				perror("");
			}
			dup2(fd, 1);
			list = list->next;
			close(fd);
		}
		else if (list && list->type == APPEND)
		{
			fd = open(list->file_name, O_CREAT | O_WRONLY | O_APPEND, 0644);
			if(fd < 0)
				perror("");
			dup2(fd, 1);
			list = list->next;
			close(fd);
		}
		else if (list && list->type == RE_INPUT)
		{
			fd = open(list->file_name, O_RDONLY, 0644);
			if(fd < 0)
				perror("");
			dup2(fd, 0);
			list = list->next;
			close(fd);
		}
		else if (list && list->type == HEREDOC)
		{
			fd = open(list->file_name, O_RDONLY, 0644);
			if(fd < 0)
				perror("");
			dup2(fd, 0);
			unlink(list->file_name);
			list = list->next;
			close(fd);
		}
		else if (list && (list->type != APPEND || list->type != RE_OUTPUT || list->type != RE_INPUT || list->type != HEREDOC))
			break ;
	}
}