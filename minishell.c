/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amounach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 12:52:57 by iel-bakk          #+#    #+#             */
/*   Updated: 2023/01/08 09:20:15 by amounach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
t_globals	g_tools = {0};

int	event(void)
{
	return (0);
}

void	free_tokens(t_tokens *tok)
{
	t_tokens	*tmp;

	tmp = tok;
	while (tok)
	{
		tok = tok->next;
		free(tmp->value);
		free(tmp);
		tmp = tok;
	}
}

void	free_redir(t_redir *tok)
{
	t_redir	*tmp;

	tmp = tok;
	while (tok)
	{
		tok = tok->next;
		free(tmp->file_name);
		free(tmp);
		tmp = tok;
	}
}

void	free_final(t_final *tok)
{
	t_final	*tmp;

	tmp = tok;
	while (tok)
	{
		tok = tok->next;
		ft_free(tmp->str);
		if (tmp->list)
			free_redir(tmp->list);
		free(tmp);
		tmp = tok;
	}
}

void	main_helper(t_env **head, t_tokens *tokens, char *line)
{
	t_final	*t;

	expande_variables(tokens, *head);
	t = convert_from_tokens_to_final(tokens);
	free_tokens(tokens);
	g_tools.global = 2;
	signal(SIGINT, SIG_IGN);
	exec_command(t, head);
	free_final(t);
	add_history(line);
}

int	free_for_main(char *line, t_tokens *tokens)
{
	if (error_checker(tokens))
	{
		free(line);
		free_tokens(tokens);
		return (1);
	}
	return (0);
}

void	loop_and_execute(t_main *all)
{
	while (1)
	{
		g_tools.global = 0;
		signal(SIGINT, handler_c);
		all->line = readline("Minishell :> ");
		if (!all->line)
			break ;
		g_tools.global = 1;
		if (*all->line)
		{
			all->tokens = parse_line(all->line);
			if (free_for_main(all->line, all->tokens))
				continue ;
			rl_event_hook = event;
			open_heredoc(all->tokens->next);
			if (g_tools.global)
				main_helper(&all->env_head, all->tokens, all->line);
			else
				free_tokens(all->tokens);
			free(all->line);
		}
		else
			free(all->line);
		system("leaks Minishell");
	}
}

int	main(int ac, char **av, char **env)
{
	t_main	all_in_one;

	(void)ac;
	(void)av;
	all_in_one.sig = 0;
	g_tools.status_sign = 0;
	rl_catch_signals = 0;
	all_in_one.env_head = creat_env_list(env);
	handler_c(all_in_one.sig);
	signal(SIGQUIT, SIG_IGN);
	loop_and_execute(&all_in_one);
	return (0);
}
