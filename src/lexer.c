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

void	stock_char_lst(t_list **lst, t_pretoken *pretoken, char *input)
{
	int			i;
	t_list		*buffer;
	t_pretoken	*allocated_pretoken;

	i = 0;
	while (input[i])
	{
		allocated_pretoken = ft_calloc(sizeof(t_pretoken), 1);
		pretoken = allocated_pretoken;
		pretoken->token = token_for_symbol(input[i]);
		pretoken->character = input[i];
		buffer = ft_lstnew(allocated_pretoken);
		if (buffer)
			ft_lstadd_back(lst, buffer);
		i++;
	}
}

int	token_for_symbol(char input)
{
	int	token;

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
	else if (input == '\\')
		token = ANTI_SLASH;
	else
		token = CHAR;
	return (token);
}

void	print_lst(t_list *lst)
{
	t_list		*cursor;
	t_pretoken	*data;

	cursor = lst;
	if (cursor == NULL)
		return ;
	while (cursor != NULL)
	{
		data = (t_pretoken *)cursor->content;
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
