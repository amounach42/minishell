/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amounach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 12:52:57 by iel-bakk          #+#    #+#             */
/*   Updated: 2023/01/04 18:52:08 by amounach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
t_globals	g_tools = {0};
int event()
{
	return 0;
}

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
	g_tools.status_sign = 0;
	rl_catch_signals = 0;
	env_head = creat_env_list(env);
	handler_c(sig);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		global = 0;
		signal(SIGINT, handler_c);
		line = readline("Minishell$ ");
		if (!line)
			break ;
		global = 1;
		if (*line)
		{
			tokens = parse_line(line);
			if (error_checker(tokens))
				continue ;
			rl_event_hook = event;
			open_heredoc(tokens->next);
			if (global)
			{
				expande_variables(tokens, env_head);
				t = convert_from_tokens_to_final(tokens);
				global = 2;
				signal(SIGINT, SIG_IGN);
				exec_command(t, env_head);
				add_history(line);
			}
		}
	}
	return (0);
}
