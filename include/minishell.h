/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trgaspar <trgaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 17:15:31 by aafounas          #+#    #+#             */
/*   Updated: 2024/10/24 18:50:00 by trgaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

typedef enum e_pretoken
{
	CHAR = 0,
	PIPE = 1,
	SPACES = 2,
	REDIRECTION_LEFT = 3,
	REDIRECTION_RIGHT = 4,
	QUOTE = 5,
	DOUBLE_QUOTE = 6,
	DASH = 7,
	DOLLAR = 8
}			t_pretoken;

typedef struct s_ptoken
{
	char			character;
	int				pretoken;
	struct s_ptoken	*next;
}	t_ptoken;

int	exit_prog(char *input);

#endif