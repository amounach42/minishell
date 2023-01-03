/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing_redirection.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amounach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 16:29:40 by amounach          #+#    #+#             */
/*   Updated: 2022/12/31 16:47:19 by amounach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

t_tokens	*get_right_out(char *line, int *i)
{
	t_tokens	*tmp;

	if (!line)
		return (NULL);
	if (line[*i + 1] == '>')
	{
		tmp = create_tokens(APPEND, ">>");
		*i += 2;
	}
	else
	{
		tmp = create_tokens(RE_OUTPUT, ">");
		*i += 1;
	}
	if (!tmp)
		return (NULL);
	return (tmp);
}

t_tokens	*get_left_out(char *line, int *i)
{
	t_tokens	*tmp;

	if (!line)
		return (NULL);
	if (line[*i + 1] == '<')
	{
		tmp = create_tokens(HEREDOC, "<<");
		*i += 2;
	}
	else
	{
		tmp = create_tokens(RE_INPUT, "<");
		*i += 1;
	}
	if (!tmp)
		return (NULL);
	return (tmp);
}

t_tokens	*get_pipe(int *i)
{
	t_tokens	*tmp;

	tmp = create_tokens(PIPE, "|");
	if (!tmp)
		return (NULL);
	*i += 1;
	return (tmp);
}

t_tokens	*get_double_quote(char *line, int *i)
{
	t_tokens	*reference;

	*i += 1;
	reference = create_tokens(DOUBLE_Q, "");
	free(reference->value);
	reference->value = inside_double_quote(line, i);
	if (!(line[*i] == '"'))
		reference->valid = -1;
	*i += 1;
	return (reference);
}

t_tokens	*get_single_quote(char *line, int *i)
{
	t_tokens	*reference;

	*i += 1;
	reference = create_tokens(SINGLE_Q, "");
	free(reference->value);
	reference->value = inside_single_quote(line, i);
	if (!(line[*i] == '\''))
		reference->valid = -1;
	*i += 1;
	return (reference);
}
