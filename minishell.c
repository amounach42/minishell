/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amounach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 12:52:57 by iel-bakk          #+#    #+#             */
/*   Updated: 2023/01/02 21:16:32 by amounach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	char		*line;
	t_env		*env_head;
	t_tokens	*tokens;
	t_final		*t;
	int			sig;

	(void)ac;
	(void)av;
	sig = 0;
	rl_catch_signals = 0;
	env_head = creat_env_list(env);
	handler_c(sig);
	signal(SIGINT, handler_c);
	while (1)
	{
		line = readline("Minishell$ ");
		if (!line)
			break ;
		if (*line)
		{
			tokens = parse_line(line);
			if (error_checker(tokens))
			{
				continue;
			}
			open_heredoc(tokens->next);
			expand_lvars(tokens, env_head);
			// while (tokens)
			// {
			// 	printf("value = %s |", tokens->value);
			// 	printf("type = %d\n", tokens->type);
			// 	tokens = tokens->next;
			// }
			t = convert_from_tokens_to_final(tokens);
			// for (t_final *l = t; l != NULL; l = l->next) {
			// 	for (int i = 0; t->str[i]; i++)
			// 		printf("%s ", t->str[i]);
			// 	t_redir *red = t->list;
			// 	while (red) {
			// 		printf("(%d) %s ", red->type, red->file_name);
			// 		red = red->next;
			// 	}
			// 	if (l->next)
			// 		printf(" | ");
			// }
			// printf("\n");
			exec_command(t, env_head);
			add_history(line);
		}
	}
	return (0);
}