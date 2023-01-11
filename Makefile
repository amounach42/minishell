NAME = Minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror

READLINE = $(shell brew --prefix readline)

INCLUDE_READLINE = $(addprefix $(READLINE),/include)

LIB_READLINE = $(addprefix $(READLINE),/lib)

SRC = minishell.c \
		env_variables.c\
		builtins.c \
		expanding.c \
		variable_expansion.c \
		ft_is.c\
		linkedlist_utils.c \
		string_manipulation.c\
		syntax_error.c \
		syntax_error_utils.c\
		tokenizer_utils.c \
		libft_functions.c\
		tokenizer.c \
		tokenizing_quotes.c \
		tokenizing_redirection.c \
		non_builtins.c \
		ft_split.c \
		almost_six.c \
		procced_to_execution.c \
		redirections.c \
		unset.c \
		cd.c \
		signals.c \
		heredoc.c \
		expande_status.c \
		procced_to_execution_utils.c\
		builtins_.c\
		builtins__.c\
		builtins_utils.c\
		envirement_variables.c \
		expanding_utils.c \
		minishell_main_tools.c \
		creat_and_verify.c \
		linked_list_tools.c \
		herdoc_tools.c \

OBJ = $(SRC:%.c=%.o)

all :$(NAME)
$(NAME) :$(OBJ) minishell.h
			$(CC) $(CFLAGS) -I $(INCLUDE_READLINE) -L $(LIB_READLINE) -lreadline $(OBJ) -o $@ 

%.o : %.c minishell.h
		$(CC) $(CFLAGS) -I $(INCLUDE_READLINE) -c $< -o $@

clean:
	@echo "\033[0;31mCleaning minishell..."
	@echo "\nRemoving binaries..."
	@rm -f $(OBJ)
	@echo "\033[0m"

fclean:
	@echo "\nDeleting objects..."
	@rm -f $(OBJ)
	@echo "\nDeleting executable..."
	@rm -f $(NAME)
	@echo "\033[0m"

re: fclean all
