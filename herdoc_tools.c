/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-bakk < iel-bakk@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 15:17:17 by iel-bakk          #+#    #+#             */
/*   Updated: 2023/01/10 15:18:54 by iel-bakk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	file_is_exists(const char *file_name)
{
	return (!access(file_name, F_OK));
}

char	*change_file_name(char *file_name, int *idx)
{
	char	*tmp;
	char	*tmp2;
	char	*tmp_num;

	tmp = ft_strjoin("/tmp/", file_name);
	if (file_is_exists(tmp))
	{
		tmp_num = ft_itoa((*idx)++);
		tmp2 = ft_strjoin(file_name, tmp_num);
		free(file_name);
		free(tmp_num);
		free(tmp);
		return (change_file_name(tmp2, idx));
	}
	else
		free(file_name);
	return (tmp);
}
