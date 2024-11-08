/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trgaspar <trgaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 17:15:31 by aafounas          #+#    #+#             */
/*   Updated: 2024/10/25 21:03:46 by trgaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

# define LEXER_INIT "minishell: lexical error"
typedef struct s_data
{
	char			*input;
	t_list			*lst;
	t_token			*token;
}	t_data;

enum e_token
{
	T_PIPE,
	T_BROKET_LEFT,
	T_BROKET_RIGHT,
	T_DOUBLE_BROKET_LEFT,
	T_DOUBLE_BROKET_RIGHT,
	T_SIMPLE_QUOTE,
	T_DOUBLE_QUOTE,
	T_DOLLAR,
	T_WHITE_SPACE,
	T_CHARACTER,
	T_WORD,
	T_VARIABLE,
	T_DELIMITER
};

typedef struct s_token
{
	char			*character;
	int				type;
}	t_token;

int		exit_prog(char *input);
int		token_for_symbol(char input);
void	stock_char_lst(t_list **lst, t_token *token, char *input);
void	print_lst(t_list *lst);
void	delete_lst(t_list *lst);
void	del(void *content);

#endif