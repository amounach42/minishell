/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_manipulation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amounach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 17:17:23 by amounach          #+#    #+#             */
/*   Updated: 2022/12/19 17:17:24 by amounach         ###   ########.fr       */
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
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	str = (char *)malloc(sizeof(char) * len);
	l = ft_strlen(s1);
	if (!str)
		return (NULL);
	i = -1;
	while (i++ <= l)
		str[i] = s1[i];
	i = 0;
	while (l < len)
		str[l++] = s2[i++];
	str[len] = '\0';
	return (str);
}

int ft_strcmp(char *s1, char *s2)
{
    int i;

    i = 0;
    if (!s1)
        return (1);
    while (s1[i] && s2[i] && s1[i] == s2[i])
        i++;
    return (s1[i] - s2[i]);
}