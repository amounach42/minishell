/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expande_status.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amounach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 19:45:18 by amounach          #+#    #+#             */
/*   Updated: 2023/01/04 19:46:13 by amounach         ###   ########.fr       */
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
