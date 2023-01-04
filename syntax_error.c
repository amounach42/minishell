/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amounach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 17:16:21 by amounach          #+#    #+#             */
/*   Updated: 2023/01/04 15:52:47 by amounach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipe_error(t_tokens *token)
{
	if (token->type == NONE && token->next)
	{
		if (token->next->type == PIPE)
		{
			ft_putstr_fd(2, "minishell: syntax error near unexpected `|'\n");
			return (1);
		}
	}
	else if ((token->type == PIPE) && (token->next))
	{
		if (token->next->type == PIPE)
		{
			ft_putstr_fd(2, "minishell: syntax error near unexpected `||'\n");
			return (1);
		}
	}
	else if (token->type == PIPE && token->next == NULL)
	{
		ft_putstr_fd(2, "minishell: syntax error near unexpected `|'\n");
		return (1);
	}
	return (0);
}

int	redirection_error(t_tokens *token)
{
	if ((redi_type(token->type) && (token->next == NULL))
		|| (is_redir(token->type) && redi_type(token->next->type)))
	{
		ft_putstr_fd(2,
			"minishell: syntax error near unexpected token `newline'\n");
		return (1);
	}
	else if ((token->type == RE_INPUT || token->type == APPEND
			|| token->type == RE_OUTPUT || token->type == HEREDOC)
		&& token->next)
	{
		if (token->next->type == RE_INPUT || token->next->type == APPEND
			|| token->next->type == RE_OUTPUT || token->next->type == HEREDOC)
		{
			write(2, "minishell: syntax error\n", 25);
			return (1);
		}
	}
	return (0);
}

int	quotes_error(t_tokens *token)
{
	if ((token->type == SINGLE_Q && token->valid == -1)
		|| (token->type == DOUBLE_Q && token->valid == -1))
	{
		ft_putstr_fd(2, "minishell: syntax error: unexpected end of file\n");
		return (1);
	}
	return (0);
}

int	error_checker(t_tokens *token)
{
	if (!token)
		return (0);
	while (token)
	{
		if (token->type == NONE || token->type == PIPE)
		{
			if (pipe_error(token))
				return (g_tools.status_sign = 2, 1);
		}
		else if (token->type == RE_INPUT || token->type == RE_OUTPUT
			|| token->type == APPEND || token->type == HEREDOC)
		{
			if (redirection_error(token))
				return (g_tools.status_sign = 2, 1);
		}
		else if (token->type == SINGLE_Q || token->type == DOUBLE_Q)
		{
			if (quotes_error(token))
				return (g_tools.status_sign = 2, 1);
		}
		token = token->next;
	}
	return (0);
}
