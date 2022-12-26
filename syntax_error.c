/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amounach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 17:16:21 by amounach          #+#    #+#             */
/*   Updated: 2022/11/09 17:03:07 by amounach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipe_error(t_tokens *token)
{
	if (token->type == NONE && token->next)
	{
		if (token->next->type == PIPE)
		{
			write(1, "minishell: syntax error near unexpected token `|'\n", 51);
			return (1);
		}
	}
	else if ((token->type == PIPE) && (token->next))
	{
		if (token->next->type == PIPE)
		{
			write(2, "minishell: syntax error near unexpected token `||'\n", 52);
			return (1);
		}
	}
	return (0);
}

int	empty_quote(t_tokens *token)
{
	if ((token->type == SINGLE_Q && token->value[0] == '\0')
		|| (token->type == DOUBLE_Q && token->value[0] == '\0'))
		return (1);
	return (0);
}

int	redirection_error(t_tokens *token)
{
	if ((redi_type(token->type) && (token->next == NULL))
		|| (is_redir(token->type) && redi_type(token->next->type)))
	{
		write(2,
			"minishell: syntax error near unexpected token `newline'\n", 57);
		return (1);
	}
	else if ((token->type == RE_INPUT || token->type == APPEND
			|| token->type == RE_OUTPUT
			|| token->type == HEREDOC) && token->next)
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
		write(2, "minishell: syntax error: unexpected end of file\n", 49);
		return (1);
	}
	return (0);
}

int	redi_type(int	type)
{
	return (type == PIPE || type == RE_INPUT || type == RE_OUTPUT
		|| type == HEREDOC || type == APPEND);
}

int is_redir(int type)
{
	return (type == RE_INPUT || type == RE_OUTPUT || type == HEREDOC
		|| type == APPEND);
}

int	error_checker(t_tokens *token)
{
	int	result;

	while (token)
	{
		if (token->type == NONE || token->type == PIPE)
			result = pipe_error(token);
		else if (token->type == RE_INPUT || token->type == RE_OUTPUT
			|| token->type == APPEND)
			result = redirection_error(token);
		else if (token->type == SINGLE_Q || token->type == DOUBLE_Q)
			result = quotes_error(token);
		token = token->next;
	}
	return (result);
}
