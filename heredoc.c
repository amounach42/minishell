/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amounach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 00:37:32 by amounach          #+#    #+#             */
/*   Updated: 2023/01/03 13:03:21 by amounach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
static int	count_size(int nb)
{
	int	i;

	i = 0;
	if (nb <= 0)
	{
		nb *= -1;
		i++;
	}
	while (nb != 0)
	{
		i++;
		nb /= 10;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*str;
	size_t	len;
	long	nb;

	nb = n;
	len = count_size(n);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	if (nb < 0)
		nb *= -1;
	str[len] = '\0';
	while (len--)
	{
		str[len] = (nb % 10) + 48;
		nb /= 10;
	}
	if (n < 0)
		str[0] = '-';
	else if (n == 0)
		str[0] = '0';
	return (str);
}

int file_is_exists(char *file_name)
{
  
    struct stat buff;
    
    return (!stat(file_name, &buff));     
}

char    *change_file_name(char *file_name, int *idx)
{
    
    if (file_is_exists(ft_strjoin("/tmp/", file_name)))
    {
        return(change_file_name(ft_strjoin("heredoc", ft_itoa((*idx)++)), idx));
        
    }
    return (ft_strjoin("/tmp/", file_name));
}

void    check_eof(char **value, int  type)
{
    char    *line;
    int     fd;
    char    *buff;
    int     idx;
    
    idx = 0;
    if (type == VARIABLE)
        *value = ft_strjoin("$", *value);
    line = ft_strdup("");
    buff = ft_strdup("");
    while (1)
    {
        line = readline(">");
        if (!line || !ft_strcmp(*value, line))
            break;
        else
            buff = ft_strjoin(buff, ft_strjoin(line, "\n"));
    } 
    *value = change_file_name("heredoc", &idx);
    puts(*value);
    fd = open(*value, O_CREAT| O_RDWR| O_APPEND, 0644);
    printf("%d\n", fd);
    ft_putstr_fd(fd, buff);
    close(fd);
}

void    open_heredoc(t_tokens *token)
{
    t_tokens    *tmp;

    tmp = token;
    while (tmp)
    {
        if (tmp->type == HEREDOC)
        {
            if (tmp->next->type == WSPACE)
            {   
                check_eof(&tmp->next->next->value, tmp->next->next->type);
            }
            else
                check_eof(&tmp->next->value, tmp->next->type);
        }
        tmp = tmp->next;
    }
}