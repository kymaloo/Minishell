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

typedef struct s_token
{
	char			*character;
	int				type;
}	t_token;

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

int		exit_prog(char *input);
int		token_for_symbol(char input);
void	stock_char_lst(t_data *data);
void	print_lst(t_data *data);
void	delete_lst(t_list *lst);
void	del(void *content);
void	init_data(t_data *data);
void	parse(t_data *data);
int		quote_is_pair(t_data *data);
void	transform_char(t_data *data, int token);

#endif