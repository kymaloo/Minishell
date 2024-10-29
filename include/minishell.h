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

typedef enum e_ptoken
{
	CHAR = 0,
	PIPE = 1,
	REDIRECTION_LEFT = 2,
	REDIRECTION_RIGHT = 3,
	QUOTE = 4,
	DOUBLE_QUOTE = 5,
	DOLLAR = 6,
	WHITE_SPACE = 7
}			t_ptoken;

typedef struct s_pretoken
{
	char			character;
	int				token;
}	t_pretoken;

int		exit_prog(char *input);
int		token_for_symbol(char input);
void	stock_char_lst(t_list **lst, t_pretoken *pretoken, char *input);
void	print_lst(t_list *lst);
void	delete_lst(t_list *lst);
void	del(void *content);

#endif