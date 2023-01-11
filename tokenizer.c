/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amounach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 03:13:45 by amounach          #+#    #+#             */
/*   Updated: 2023/01/08 04:28:57 by amounach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tokens	*create_tokens(int type, char *value)
{
	t_tokens	*tokens;

	tokens = (t_tokens *)malloc(sizeof(t_tokens));
	if (!tokens)
		return (NULL);
	tokens->type = type;
	tokens->valid = 1;
	tokens->space = 0;
	tokens->value = ft_strdup(value);
	tokens->next = NULL;
	return (tokens);
}

int	is_special(char c)
{
	char	*special;
	int		i;

	if (!c)
		return (0);
	special = ft_strdup(" |><'\"");
	i = 0;
	while (special[i])
	{
		if (special[i] == c)
			return (free(special), 1);
		i++;
	}
	free(special);
	return (0);
}

t_tokens	*parse_line(char *line)
{
	int			i;
	t_tokens	*head;
	t_tokens	*tmp;

	i = 0;
	head = create_tokens(NONE, "NONE");
	tmp = head;
	while (line[i])
	{
		while (tmp->next)
			tmp = tmp->next;
		if (line[i] == ' ')
		{
			if (line[i + 1] && line[i + 1] != ' ')
				tmp->space = 1;
			i++;
		}
		else if (!is_special(line[i]))
			tmp->next = get_word(line, &i);
		else
			tmp->next = get_special(line, &i);
	}
	return (head);
}
