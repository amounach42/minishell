/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amounach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 15:12:54 by amounach          #+#    #+#             */
/*   Updated: 2023/01/04 15:12:57 by amounach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	empty_quote(t_tokens *token)
{
	if ((token->type == SINGLE_Q && token->value[0] == '\0')
		|| (token->type == DOUBLE_Q && token->value[0] == '\0'))
		return (1);
	return (0);
}

int	redi_type(int type)
{
	return (type == PIPE || type == RE_INPUT || type == RE_OUTPUT
		|| type == HEREDOC || type == APPEND);
}

int	is_redir(int type)
{
	return (type == RE_INPUT || type == RE_OUTPUT || type == HEREDOC
		|| type == APPEND);
}
