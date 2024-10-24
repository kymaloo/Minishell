/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trgaspar <trgaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 18:34:49 by trgaspar          #+#    #+#             */
/*   Updated: 2024/10/24 18:55:29 by trgaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void   stock_char_lst(t_ptoken *ptoken, char *input)
{
    int i;

    i = 0;
    while (input[i])
    {
        
    }
}

int token_for_symbol(char input)
{
    int token;

    token = 0;
    if (input == '|')
        token = PIPE;
    else if (input == ' ')
        token = SPACES;
    else if (input == '<')
        token = REDIRECTION_LEFT;
    else if (input == '>')
        token = REDIRECTION_RIGHT;
    else if (input == '\'')
        token = QUOTE;
    else if (input == '"')
        token = DOUBLE_QUOTE;
    else if (input == '-')
        token = DASH;
    else if (input == '$')
        token = DOLLAR;
    else
        token = CHAR;
    return (token);
}
