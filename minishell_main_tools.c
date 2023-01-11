/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_main_tools.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-bakk < iel-bakk@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 15:05:31 by iel-bakk          #+#    #+#             */
/*   Updated: 2023/01/10 15:07:09 by iel-bakk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tokens(t_tokens *tok)
{
	t_tokens	*tmp;

	tmp = tok;
	while (tok)
	{
		tok = tok->next;
		free(tmp->value);
		free(tmp);
		tmp = tok;
	}
}

void	free_redir(t_redir *tok)
{
	t_redir	*tmp;

	tmp = tok;
	while (tok)
	{
		tok = tok->next;
		free(tmp->file_name);
		free(tmp);
		tmp = tok;
	}
}

void	free_final(t_final *tok)
{
	t_final	*tmp;

	tmp = tok;
	while (tok)
	{
		tok = tok->next;
		ft_free(tmp->str);
		if (tmp->list)
			free_redir(tmp->list);
		free(tmp);
		tmp = tok;
	}
}
