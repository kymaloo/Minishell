
NAME	:= minishell

CFLAGS	:= -Wextra -Wall -Werror -g3

LDFLAGS	:= -lreadline

HEADERS	:= -Iinclude

SRCS	:= 	src/minishell.c src/Exec/command_info.c src/Exec/execute_utils.c \
			src/Exec/path_utils.c src/Exec/process_utils.c src/Exec/redirection_utils.c src/builtins/cd.c \
			src/builtins/echo.c src/builtins/execute_builtin.c src/builtins/exit.c src/builtins/pwd.c \
			src/builtins/env.c src/builtins/export_utils.c src/builtins/utils.c src/builtins/utils2.c \
			src/builtins/export.c src/builtins/unset.c \
			src/parsing/stock_new_lst.c		\
			src/parsing/stock_new_lst_utils.c		\
			src/parsing/lst_token.c		\
			src/parsing/lst_utils.c		\
			src/parsing/lst_token_utils.c		\
			src/parsing/parse_quote.c		\
			src/parsing/parse_dollar.c		\
			src/parsing/parse_init.c \
			src/parsing/expand.c \
			src/parsing/expand_utils.c \

OBJS	:= ${SRCS:.c=.o}

LIBFT	:= ./libft
LIBFT_EXE := ./libft/libft.a

all: $(NAME)

n:
	norminette src/parsing include/

r:
	make re && ./minishell

v:
	make re && valgrind --leak-check=full -s ./minishell

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

$(NAME): $(OBJS)
	@echo "\033[33m----Compiling ${NAME}---"
	@$(MAKE) -C $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT_EXE) $(LDFLAGS) $(HEADERS) -o $(NAME)
	@echo "\033[32m----${NAME} Compiled!----\033[0m"
	

clean:
	@echo "\033[31m----Cleaning object files----\033[0m"
	@rm -rf $(OBJS)
	@$(MAKE) clean -C  $(LIBFT)

fclean: clean
	@echo "\033[31m----Cleaning all generated files----\033[0m"
	@rm -rf $(NAME)
	@$(MAKE) fclean -C  $(LIBFT)

re: fclean all

.PHONY: all, clean, fclean, re