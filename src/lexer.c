/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trgaspar <trgaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 18:34:49 by trgaspar          #+#    #+#             */
/*   Updated: 2024/10/25 18:03:24 by trgaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void   stock_char_lst(t_list **lst, t_pretoken *pretoken, char *input)
{
    int i;
    t_list *buffer;
	t_pretoken	*allocated_pretoken;

    i = 0;
    while (input[i])
    {
        //pretoken->token = token_for_symbol(input[i]);
		//pretoken->character = input[i];
		allocated_pretoken = ft_calloc(sizeof(t_pretoken), 1);
		allocated_pretoken = pretoken;
        buffer = ft_lstnew(allocated_pretoken);
        if (buffer)
            ft_lstadd_back(lst, buffer);
		printf("Char : %c\n token : %d\n\n", allocated_pretoken->character, allocated_pretoken->token);
        i++;
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

void	*print_lst(t_pretoken *pretoken)
{
    printf("Char : %c\n token : %d\n\n", pretoken->character, pretoken->token);
	return (0);
}
