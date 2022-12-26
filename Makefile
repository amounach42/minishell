NAME = Minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror #-g -fsanitize=address

SRC = minishell.c \
		tokenizer.c \
		tokenizing_redirection.c \
		tokenizing_quotes.c \
		linkedlist_utils.c \
		syntax_error.c \
		pwd.c \
		env_variables.c\
		expending.c \
		string_manipulation.c\

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