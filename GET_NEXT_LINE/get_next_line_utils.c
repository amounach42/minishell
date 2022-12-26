/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-bakk <iel-bakk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 14:59:35 by iel-bakk          #+#    #+#             */
/*   Updated: 2021/12/20 15:48:52 by iel-bakk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*mifree(char	*str, char	*s)
{
	if (str)
		free(str);
	if (s)
		free(s);
	return (NULL);
}

t_data	mifree_data(t_data data)
{
	data.faill = 1;
	mifree(data.line, data.remainder);
	return (data);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		len;
	int		l;
	int		i;
	char	*str;

	if (!s1)
		len = ft_strlen(s2);
	else
		len = ft_strlen(s1) + ft_strlen(s2);
	str = (char *)malloc(sizeof(char) * len + 1);
	if (!str)
		return (NULL);
	i = 0;
	if (s1)
	{
		i = -1;
		while (s1[++i])
			str[i] = s1[i];
	}
	l = -1;
	while (s2[++l])
		str[l + i] = s2[l];
	str[l + i] = '\0';
	mifree(s1, 0);
	return (str);
}

size_t	ft_strlcpy(char *dst, char *src, size_t dstsize)
{
	size_t	r;
	size_t	i;

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
