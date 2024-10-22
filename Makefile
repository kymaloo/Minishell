# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aafounas <aafounas@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/17 15:29:02 by aafounas          #+#    #+#              #
#    Updated: 2024/09/17 17:14:48 by aafounas         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
SRCS = minishell.c
OBJS = ${SRCS:.c=.o}

CC = cc
CFLAGS = -g3 -Wall -Werror -Wextra
RM = rm -f

all: ${NAME}

${NAME}: ${OBJS}
		@echo "\033[33m----Compiling ${NAME}---"
		${CC} ${CFLAGS} ${OBJS} -o ${NAME
		@echo "\033[32m${NAME} Compiled!\033[0m"

clean:
		@echo "\033[31m----Cleaning object files----\033[0m"
		make -C clean
		${RM} ${OBJS}

fclean: clean
		@echo "\033[31m----Claning all generated files----\033[0m"
		make -C ${LIBFT_DIR} fclean
		${RM} ${NAME}

re:	fclean all

.PHONY: all clean fclean re