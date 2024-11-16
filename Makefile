NAME	:= minishell

CFLAGS	:= -Wextra -Wall -Werror -g3

LDFLAGS	:= -lreadline

HEADERS	:= -Iinclude

SRCS	:= 	src/minishell.c \
			src/builtins.c  \
			src/parsing/lexer.c		\
			src/init.c \

OBJS	:= ${SRCS:.c=.o}

LIBFT	:= ./libft
LIBFT_EXE := ./libft/libft.a

all: $(NAME)

n:
	norminette src/ include/

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
	@echo "\033[32m${NAME} Compiled!\033[0m"
	

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