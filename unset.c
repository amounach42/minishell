/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amounach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 20:11:44 by amounach          #+#    #+#             */
/*   Updated: 2022/12/28 16:52:56 by amounach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void match_variables(t_env **env, char **str)
{
  int i;

  t_env *tmp = *env;
  i = 1;
  while (str[i])
  {
    tmp = *env;
    while (tmp)
    {
      if (strcmp(str[i], tmp->v_name) == 0)// TODO: use ft_strcmp
      {
        // printf ("var name:%s\n",tmp->v_name);
        printf ("string: %s\n", str[i]);
        delete_onev(env, tmp);
      }
      tmp = tmp->next;
    }
    i++;
  }
}

void  unset(t_env **env, char **str)
{
    match_variables(env, str);
}
