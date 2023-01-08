/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expande_status.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-bakk < iel-bakk@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 12:28:53 by iel-bakk          #+#    #+#             */
/*   Updated: 2023/01/07 12:29:07 by iel-bakk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_status(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '?')
	{
		return (ft_itoa(g_tools.status_sign));
	}
	return (NULL);
}

void	expand_status(t_params *param, char *status)
{
	char	*storage;

	storage = (char *)malloc((sizeof(char) * ((param->count) + 1)));
	ft_strlcpy(storage, param->line + (param->cpt), (param->count) + 1);
	param->buffer = ft_strjoin(param->buffer, storage);
	param->buffer = ft_strjoin(param->buffer, status);
	param->count = 0;
	param->i += 2;
	param->cpt = param->i;
}
