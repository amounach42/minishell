/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-bakk < iel-bakk@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 03:14:04 by amounach          #+#    #+#             */
/*   Updated: 2022/12/26 18:50:28 by iel-bakk         ###   ########.fr       */
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
	FIILE,
	COMMAND,
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

typedef struct s_redir{
	char			*file_name;
	int				type;
	struct	s_redir	*next;
}	t_redir;

typedef struct s_final
{
	char			**str;
	t_redir			*list;
	struct	s_final	*next;
}	t_final;

typedef	struct s_env
{
	char			*v_name;
	char			*v_value;
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
char		**ft_split(char *s, char c);
char		*malloc_word(char *str, char c);
char		**ft_free(char **str);
int			count_words(char *str, char c);

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
t_env		*creat_env_node(char *v_name);
t_env		*creat_env_list(char **env);
void		delete_onev(t_env **head, t_env *to_d);
void		delete_env_list(t_env **head);
void		delete_env_node(t_env **to_delete);
void    	expand_lvars(t_tokens *list);
void 		change_value(t_tokens *token);
char 		*get_variable(char *line);
void 		increment(int *i, int *count);
void 		get_last_word(char **buffer, char *line, int cpt, int count);
int 		get_buffer(char *line, char **buffer, int *i, int j, int *cpt, int *count, int len);
void 		intialize(int *i, int *j, int *len, int *cpt, int *count);
char 		*get_v_value(char *env_name, t_env *env);
int 		is_variable(char *line);
int 		is_character(int c);
int 		is_dollar(int c);


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

// builtins
void		mi_env(t_env *list);
void    	call_builtin(char **arg, t_env *list);
int 		mi_pwd(void);
int			mi_echo(char **arg);
int 		ft_strcmp(char *s1, char *s2);
int			check_n_option(char *str);
void		ft_putstr_fd(int fd, char *str);
int			mi_cd(char **arg);
void		mi_export(char **arg, t_env *list);
void		print_export(t_env	*list);
void		export_cases(char **arg, t_env *list);
void		modify_envar(char *name, char *op_value, t_env *list);
void		try_to_creat(char *new, t_env *list);

// check if builtin or not
int 		compare_to_biultin(char *str);
int 		check_builtin(char *str, t_env *list);
void		non_builtin(char **param, char **env);

// creating a pipe
int			*creat_pipe(void);

// final linked list

t_final 	*creat_final_node(int tab_len);

// redirection functions
t_redir 	*creat_redir_node(char *file_name, int type);
int			verify_is_word_type(t_tokens *test);
int			calc_cmd_len(t_tokens *list);
t_final		*lvlup_ultimate(t_tokens *list);
void		final_commad(t_final **head, t_tokens **list, int len);

#endif