# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: r <r@student.42.fr>                        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/17 15:29:02 by aafounas          #+#    #+#              #
#    Updated: 2024/11/16 23:30:59 by r                ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:= minishell

CFLAGS	:= -Wextra -Wall -Werror -g3
LDFLAGS	:= -lreadline

HEADERS	:= -Iinclude

SRCS	:= 	src/minishell.c src/Exec/command_info.c src/Exec/execute_utils.c \
			src/Exec/path_utils.c src/Exec/process_utils.c src/Exec/redirection_utils.c src/builtins/cd.c \
			src/builtins/echo.c src/builtins/execute_builtin.c src/builtins/exit.c src/builtins/pwd.c src/builtins/env.c src/ast.c\

OBJS	:= ${SRCS:.c=.o}

LIBFT	:= ./libft
LIBFT_EXE := ./libft/libft.a

all: $(NAME)

n:
	norminette src/ include/

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