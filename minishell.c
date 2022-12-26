#include "minishell.h"

int	main(int ac, char **av,char **env)
{
	char	*line;
	// int		i;
	t_env	*env_head;
	(void)ac;
	(void)av;
	t_tokens *tokens;

	// i = 0;
	// while (env[i])
	// {
	// 	printf("%s\n", env[i]);
	// 	i++;
	// }
	env_head = creat_env_list(env);
	if (!env_head)
		return (0);
	// t_env = env_head;
	// while (env_head)
	// {
	// 	printf("%s\n",env_head->v_name);
	// 	env_head = env_head->next;
	// }
	// // while (1);

	//delete_env_list(&t);
	// delete_onev(&env_head, env_head);
	// tokens = NULL;
	// print_until_ws(tokens);
	printf("%s\n", get_v_value("HOME", env_head));

	while (1)
	{
		line = readline("Minishell$ ");
		if (!line)
			return 0;
		// printf("%s\n", line);
		tokens = parse_line(line);
		expand_lvars(tokens);
		// print_until_ws(line);
		// printf("%d\n", get_value(line, env_head));
		// printf("%s\n", get_v_value("$HOME", env_head));
		// input_append_error(tokens);
		// printf("%s\n", getenv("hello"));
		// redirection_error(tokens);
        // quotes_error(tokens);
        // pipe_error(tokens);
		error_checker(tokens);
		while (tokens)
		{
			printf(" ------- %s\n", tokens->value);
			printf(" ------- %d\n", tokens->type);
			// printf(" ------- %d\n", tokens->space);
			tokens = tokens->next;
		}
		add_history(line);
	}
}
