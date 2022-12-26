/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-bakk <iel-bakk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 14:59:23 by iel-bakk          #+#    #+#             */
/*   Updated: 2021/12/24 10:05:04 by iel-bakk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	michr(char *s, char c)
{
	int	i;

	i = 0;
	if (!s)
		return (1);
	while (s[i])
	{
		if (s[i] == c)
			return (0);
		i++;
	}
	return (1);
}

char	*miread(int fd, char *str)
{
	char	*buff;
	int		n_b;

	buff = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buff)
		return (mifree(str, 0));
	n_b = 1;
	while (michr(str, 10) && n_b)
	{
		n_b = read(fd, buff, BUFFER_SIZE);
		if (n_b < 0)
			return (mifree(str, buff));
		buff[n_b] = 0;
		str = ft_strjoin(str, buff);
	}
	mifree(buff, 0);
	if (ft_strlen(str) == 0)
		return (mifree(str, 0));
	return (str);
}

t_data	mifilter(char	*str)
{
	int		i;
	int		len;
	t_data	data;

	i = 0;
	data.faill = 0;
	while (str[i] != '\n' && str[i])
		i++;
	i += (str[i] == '\n');
	len = ft_strlen(str + i);
	data.line = (char *)malloc(sizeof(char) * i + 1);
	if (!data.line)
		return (mifree_data(data));
	ft_strlcpy(data.line, str, i + 1);
	if (str[len])
	{
		data.remainder = (char *)malloc(sizeof(char) * (len + 1));
		if (!data.remainder)
			return (mifree_data(data));
		ft_strlcpy(data.remainder, str + i, len + 1);
	}
	else
		data.remainder = 0;
	mifree(str, 0);
	return (data);
}

char	*get_next_line(int fd)
{
	static char	*reminder;
	t_data		line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	reminder = miread(fd, reminder);
	if (!reminder)
		return (0);
	line = mifilter(reminder);
	if (line.faill)
		return (NULL);
	reminder = line.remainder;
	return (line.line);
}
