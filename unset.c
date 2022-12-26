/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amounach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 20:11:44 by amounach          #+#    #+#             */
/*   Updated: 2022/12/26 20:11:56 by amounach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void del_first_node(t_env **head_ref, char *key)
{
  t_env *to_delete;

  to_delete = *head_ref;
  if (!*head_ref)
    return;
  if (strcmp(key, to_delete->v_name) == 0)
  {
    to_delete = *head_ref;
    head_ref = to_delete->next;
    head_ref = to_delete->next;
    free(to_delete);
  }
}