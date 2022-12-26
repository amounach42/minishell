/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amounach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 03:13:45 by amounach          #+#    #+#             */
/*   Updated: 2022/12/13 15:16:35 by amounach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strdup(char *s1)
{
	char	*str;
	int		i;

	i = 0;
	str = (char *)malloc(sizeof(char) * ft_strlen(s1) + 1);
	if (!str)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

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

int	ft_strlcpy(char *dst,char *src, int dstsize)
{
	int	r;
	int	i;

	i = 0;
	r = 0;
	while (src[i])
		i++;
	if (dstsize == 0)
		return (i);
	while (src[r] && r < dstsize - 1)
	{
		dst[r] = src[r];
		r++;
	}
	dst[r] = '\0';
	return (i);
}

int	is_special(char c)
{
	char	*special;

	if (!c)
		return (0);
	special = " |><'\"";
	while (*special)
	{
		if (*special == c)
			return (1);
		special++;
	}
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