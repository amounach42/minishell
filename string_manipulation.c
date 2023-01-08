/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_manipulation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amounach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 12:38:41 by iel-bakk          #+#    #+#             */
/*   Updated: 2023/01/08 04:30:10 by amounach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin(char *s1, char *s2)
{
	int		len;
	int		l;
	int		i;
	char	*str;

	if (!s1)
		s1 = ft_strdup("");
	len = ft_strlen(s1) + ft_strlen(s2);
	str = (char *)malloc(sizeof(char) * (len + 1));
	l = ft_strlen(s1);
	if (!str)
		return (NULL);
	i = -1;
	while (++i <= l)
		str[i] = s1[i];
	i = 0;
	while (l < len)
		str[l++] = s2[i++];
	str[len] = '\0';
	return (str);
}
