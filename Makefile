NAME = Minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror #-g -fsanitize=address

SRC = minishell.c \
		env_variables.c\
		builtins.c \
		expending.c \
		linkedlist_utils.c \
		pwd.c \
		string_manipulation.c\
		syntax_error.c \
		tokenizer_utils.c \
		tokenizer.c \
		tokenizing_quotes.c \
		tokenizing_redirection.c \
		non_builtins.c \
		ft_split.c \
		almost_six.c \

OBJ = $(SRC:%.c=%.o)

all :$(NAME)
$(NAME) :$(OBJ) minishell.h
			$(CC) $(CFLAGS) $(OBJ) -o $@ -lreadline

%.o : %.c minishell.h
		$(CC) $(CFLAGS) -c $< -o $@

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
