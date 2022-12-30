#include "minishell.h"


void	handler_c(int sig)
{
	(void) sig;

	rl_replace_line("", 0);
	write(1, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
}

int	main(int ac, char **av, char **env)
{
	char	*line;
	// int		i;
	t_env	*env_head;
	(void)ac;
	(void)av;
	t_tokens *tokens;
	t_final  *t;

	// i = 0;
	// while (env[i])
	// {
	// 	printf("%s\n", env[i]);
	// 	i++;
	// }
	
	env_head = creat_env_list(env);
	// t_env *tmps;
	// tmps = env_head;
	// while (tmps)
	// {
	// 	printf("%s\n", tmps->v_name);
	// 	printf("%s\n", tmps->v_value);
	// 	tmps = tmps->next;
	// }
	

	
	if (!env_head)
		return (0);
	// i = check_builtin(av[1], env_head);
	// if (i == 1)
	// 	non_builtin(av + 1, env);
	// else if (i == 2)
	// 	// path already exists
	// else if (i == 3)
	// 	// creat a path for the command
	// else
	// 	perror("error");
	// while (env_head)
	// {
	// 	printf("%s",env_head->v_name);
	// 	if (env_head->v_value)
	// 		printf("=%s",env_head->v_value);
	// 	printf("\n");
	// 	env_head = env_head->next;
	// }

	// while (1);

	// delete_env_list(&t);
	// delete_onev(&env_head, env_head);
	// tokens = NULL;
	t_tokens *tmp;
	rl_catch_signals = 0;
	signal(SIGINT, handler_c);
	while (1)
	{
		line = readline("Minishell$ ");
		if (!line)
			exit (0);
		tokens = parse_line(line);
		tmp = tokens->next;
		error_checker(tokens);
		expand_lvars(tokens);
		t = lvlup_ultimate(tmp);
		call_builtin(t->str, env_head);
		unset(&env_head, t->str);
		// printf ("%s\n",get_home(env_head));
		// while (t->str[i])
		// {
		// 	printf("\n\nstr:%s\n", t->str[i]);
		// 	i++;
		// }
		// while (tokens)
		// {
		// 	printf(" ------- %s\n", tokens->value);
		// 	printf(" ------- %d\n", tokens->type);
		// 	printf(" ------- %d\n", tokens->space);
		// 	tokens = tokens->next;
		// }
		add_history(line);
		// i = 0;
	}
}
