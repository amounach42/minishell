/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-bakk <iel-bakk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 14:59:47 by iel-bakk          #+#    #+#             */
/*   Updated: 2021/12/20 16:06:50 by iel-bakk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include<stdlib.h>
# include<unistd.h>

typedef struct s_data
{
	char	*remainder;
	char	*line;
	int		faill;
}t_data;

int		ft_strlen(char *str);
char	*get_next_line(int fd);
char	*mifree(char *str, char *s);
char	*ft_strjoin(char *s1, char *s2);
t_data	mifree_data(t_data data);
size_t	ft_strlcpy(char *dst, char *src, size_t dstsize);

#endif
