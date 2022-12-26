/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amounach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 03:14:04 by amounach          #+#    #+#             */
/*   Updated: 2022/12/22 21:25:57 by amounach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef enum e_tokens
{
	NONE,
	PIPE,
	WSPACE,
	SINGLE_Q,
	DOUBLE_Q,
	RE_INPUT,
	RE_OUTPUT,
	APPEND,
	HEREDOC,
	WORD,
	VARIABLE,
}	e_tokens;

typedef struct s_tokens
{
	int				type;
	char			*value;
	int				valid;
	int				space;
	struct s_tokens	*next;
	struct s_tokens *prev;
}			t_tokens;

typedef	struct s_env
{
	char	*v_name;
	char	*v_value;	
	struct	s_env	*next;
}	t_env;

// Tokenizer
t_tokens	*create_tokens(int type, char *value);
int			is_space(t_tokens**token, char *line);
int			is_pipe(t_tokens **tokens, char *line);
int			redi_type(int	type);
int 		is_redir(int type);
// Builtins

int			ft_pwd(void);

// Linked list utils
t_tokens	*new_node(int type, char *value);
void		delete_first_node(t_tokens **head);
void		push_front(t_tokens **head, t_tokens *node);
void		push_back(t_tokens **head, t_tokens *node);
void		display(t_tokens *head);

// Functions from libft and other projects
char		*ft_strdup(char *s1);
int			ft_strlen(char *str);
int			ft_strlcpy(char *dst, char *src, int dstsize);
char		*ft_strjoin(char *s1, char *s2);
int			ft_strcmp(char *s1, char *s2);

// Syntax Error
int			pipe_error(t_tokens *token);
int			redirection_error(t_tokens *token);
int			input_append_error(t_tokens *token);
int			empty_quote(t_tokens *token);
int			redirection_error(t_tokens *token);
int			quotes_error(t_tokens *token);
int			heredoc_error(t_tokens *token);
int			error_checker(t_tokens *token);

//parsing functions
char		*get_v_name(char *str);
char 	*get_variable(char *line);
t_env		*creat_env_node(char *v_name);
t_env		*creat_env_list(char **env);
void		delete_onev(t_env **head, t_env *to_d);
void		delete_env_list(t_env **head);
void		delete_env_node(t_env **to_delete);
void    	expand_lvars(t_tokens *list);
int			is_dollar(int c);
// char		*print_until_ws(char *line);
// int			get_value(char *line, t_env *var);
char		*get_v_value(char *env_name, t_env *env);
// jesus tests
t_tokens	*parse_line(char *line);
t_tokens	*get_special(char *line, int *i);
t_tokens	*get_word(char *line, int *i);
char		*allocat_word(char *line, int *i);
int			is_special(char c);
t_tokens	*get_left_out(char *line, int *i);
t_tokens	*get_right_out(char *line, int *i);
t_tokens	*get_pipe(int *i);
t_tokens	*get_double_quote(char *line, int *i);
char		*inside_double_quote(char *line, int *i);
char		*inside_single_quote(char *line, int *i);
t_tokens	*get_single_quote(char *line, int *i);

#endif

/**
 * 	looping over the line we get from the readline to create tokens (|, space, quotes, redirections)
 * 	create function to detect each one of those tokens
 * 
 * 	checking syntax error
 * 	if we found PIPE in the beginning of the line or at the end of it.
 * 
 *  > redirection output
 * 	< redirection input
 * 	<< heredoc
 * 	>> append
 * 	
*/