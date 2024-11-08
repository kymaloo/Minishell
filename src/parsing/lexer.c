/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trgaspar <trgaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 18:34:49 by trgaspar          #+#    #+#             */
/*   Updated: 2024/10/25 21:21:01 by trgaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	stock_char_lst(t_data *data)
{
	int			i;
	t_list		*buffer;
	t_token		*allocated_token;

	i = 0;
	while (data->input[i])
	{
		allocated_token = ft_calloc(sizeof(t_token), 1);
		token = allocated_token;
		token->type = token_for_symbol(input[i]);
		token->character = ft_calloc(2, sizeof(char));
		token->character[0] = input[i];
		token->character[1] = '\0';
		buffer = ft_lstnew(allocated_token);
		if (buffer)
			ft_lstadd_back(lst, buffer);
		i++;
	}
}

int	token_for_symbol(char input)
{
	if (input == '|')
		token = PIPE;
	else if (input == '<')
		token = REDIRECTION_LEFT;
	else if (input == '>')
		token = REDIRECTION_RIGHT;
	else if (input == '\'')
		token = QUOTE;
	else if (input == '"')
		token = DOUBLE_QUOTE;
	else if (input == '$')
		token = DOLLAR;
	else if (input == 32 || (input >= 9 && input <= 13))
		token = WHITE_SPACE;
	else if (ft_isprint(input))
		token = CHAR;
	else
	{
		printf(LEXER_INIT);
		return (1);
	}
	return (0);
}

void	print_lst(t_list *lst)
{
	t_list		*cursor;
	t_token	*data;

	cursor = lst;
	if (cursor == NULL)
		return ;
	while (cursor != NULL)
	{
		data = (t_token *)cursor->content;
		printf("Character: %c, Token: %d\n", data->character, data->token);
		cursor = cursor->next;
	}
	printf("\n");
}

void	delete_lst(t_list *lst)
{
	t_list	*cursor;

	cursor = lst;
	ft_lstclear(&cursor, del);
}

void	del(void *content)
{
	free(content);
}
