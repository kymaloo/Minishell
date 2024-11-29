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

#include "../include/minishell.h"

void	stock_char_lst(t_data *data)
{
	int			i;
	t_list		*buffer;

	i = 0;
	data->lst = NULL;
	while (data->input[i])
	{
		buffer = ft_lstnew(data->input[i], token_for_symbol(data->input[i]));
		ft_lstadd_back(&data->lst, buffer);
		i++;
	}
}

int	token_for_symbol(char input)
{
	int	token;

	token = 0;
	if (input == '|')
		token = T_PIPE;
	else if (input == '<')
		token = T_BROKET_LEFT;
	else if (input == '>')
		token = T_BROKET_RIGHT;
	else if (input == '\'')
		token = T_SIMPLE_QUOTE;
	else if (input == '"')
		token = T_DOUBLE_QUOTE;
	else if (input == '$')
		token = T_DOLLAR;
	else if (input == 32 || (input >= 9 && input <= 13))
		token = T_WHITE_SPACE;
	else
		token = T_CHARACTER;
	return (token);
}

void	print_lst(t_data *data)
{
	t_list		*cursor;

	cursor = data->lst;
	if (cursor == NULL)
		return ;
	while (cursor != NULL)
	{
		printf("Character: %c  Token: %d\n", cursor->character, cursor->type);
		cursor = cursor->next;
	}
	printf("\n");
}

int	quote_is_pair(t_data *data)
{
	int	status;

	data->quote_is_paire = 0;
	status = EXIT_SUCCESS;
	while (data->input[data->quote_is_paire])
	{
		if (data->input[data->quote_is_paire] == '"')
		{
			status = simple_or_double(data, '"');
			if (status == EXIT_FAILURE)
				return (status);
		}
		if (data->input[data->quote_is_paire] == '\'')
		{
			status = simple_or_double(data, '\'');
			if (status == EXIT_FAILURE)
				return (status);
		}
		data->quote_is_paire++;
	}
	return (0);
}

int	simple_or_double(t_data *data, char type)
{
	int	pair;

	pair = 1;
	if (data->input[data->quote_is_paire] == type)
	{
		data->quote_is_paire++;
		while (data->input[data->quote_is_paire] && data->input[data->quote_is_paire] != type)
			data->quote_is_paire++;
		if (data->input[data->quote_is_paire] == type)
			pair++;
		if (!data->input[data->quote_is_paire] && pair % 2 != 0)
			return (1);
	}
	return (0);
}

void	transform_char(t_data *data, int token)
{
	t_list		*cursor;
	int			cpt;

	cpt = 0;
	cursor = data->lst;
	if (cursor == NULL)
		return ;
	if (check_quote_is_closed(data, token) == 1)
		return ;
	while (cursor != NULL)
	{
		if (cursor && cursor->next && cursor->type == token && cpt % 2 == 0)
		{
			if (cursor->type == token)
				cpt++;
			cursor = cursor->next;
			while (cursor != NULL && cursor->type != token)
			{
				cursor->type = T_CHARACTER;
				cursor = cursor->next;
			}
		}
		else
			cursor = cursor->next;
	}
}

int	check_quote_is_closed(t_data *data, int token)
{
	t_list	*cursor;

	cursor = data->lst;
	while (cursor && cursor->next && cursor->type != token)
		cursor = cursor->next;
	while (cursor && cursor->next)
	{
		cursor = cursor->next;
		if (cursor->type == token)
			return (0);
	}
	return (1);
}

void	check_dollar(t_data *data, int token)
{
	t_list	*cursor;
	int		cpt;

	cpt = 0;
	cursor = data->lst;
	if (check_quote_is_closed(data, token) == 1)
		return ;
	if (!is_dollar_in_double_quotes(data))
		return ;
	while (cursor && cursor->next)
	{
		if (cursor->character == '"' && cpt % 2 == 0)
		{
			if (cursor && cursor->next && cursor->type == token)
				cpt++;
			while (cursor && cursor->next && cursor->character != '$')
				cursor = cursor->next;
			while (cursor && cursor->next && cursor->character == '$' && cursor->next->character == '$')
				cursor = cursor->next;
			if (cursor && cursor->next && cursor->next->type != T_WHITE_SPACE)
				cursor->type = T_DOLLAR;
		}
		else
			cursor = cursor->next;
	}
}

bool is_dollar_in_double_quotes(t_data *data)
{
    bool in_double_quotes;
	t_list	*cursor;

	cursor = data->lst;
	in_double_quotes = false;
    while (cursor)
	{
        if (cursor->character == '"')
            in_double_quotes = !in_double_quotes;
		else if (cursor->character == '$' && in_double_quotes)
            return (true);
        cursor = cursor->next;
    }
    return (false);
}

int	count_handle_quote(t_list *cursor, int type)
{
	t_list	*tmp;
	int		i;

	tmp = cursor;
	i = 1;
	tmp = tmp->next;
	while (tmp && tmp->type != type)
	{
		i++;
		tmp = tmp->next;
	}
	if (tmp)
		i++;
	return (i);
}

void handle_quote(t_data *data, t_list **cursor, int type)
{
	int		i;
	t_list	*start;

	i = count_handle_quote(*cursor, type);
	data->str_stock_lst = malloc(sizeof(char) * (i + 1));
	if (!data->str_stock_lst)
		return ;
	start = *cursor;
	i = 0;
	data->str_stock_lst[i] = start->character;
	i++;
	start = start->next;
	while (start && start->type != type)
	{
		data->str_stock_lst[i++] = start->character;
		start = start->next;
	}
	if (start)
	{
		data->str_stock_lst[i++] = start->character;
		start = start->next;
	}
	data->str_stock_lst[i] = '\0';

	*cursor = start;
}

void handle_dollar(t_data *data, t_list **cursor)
{
	int		i;
	t_list	*start;

	i = count_handle_dollar(*cursor);
	data->str_stock_lst = malloc(sizeof(char) * (i + 1));
	if (!data->str_stock_lst)
		return;
	start = *cursor;
	i = 0;
	while (start && (start->type == T_DOLLAR || start->type == T_CHARACTER))
	{
		data->str_stock_lst[i++] = start->character;
		start = start->next;
	}
	data->str_stock_lst[i] = '\0';
	*cursor = start;
}

void handle_character(t_data *data, t_list **cursor)
{
	int		i;
	t_list	*start;

	i = count_handle_character(*cursor);
	data->str_stock_lst = malloc(sizeof(char) * (i + 1));
	if (!data->str_stock_lst)
		return;
	start = *cursor;
	i = 0;
	while (start && start->type == T_CHARACTER)
	{
		data->str_stock_lst[i++] = start->character;
		start = start->next;
	}
	data->str_stock_lst[i] = '\0';
	*cursor = start;
}

int count_handle_dollar(t_list *cursor)
{
	t_list	*tmp;
	int		i;

	if (!cursor || cursor->type != T_DOLLAR)
		return (0);
	tmp = cursor;
	i = 0;
	while (tmp && (tmp->type == T_DOLLAR || tmp->type == T_CHARACTER))
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}


int count_handle_character(t_list *cursor)
{
	t_list *tmp;
	int i;

	if (!cursor || cursor->type != T_CHARACTER)
		return 0;

	tmp = cursor;
	i = 0;
	while (tmp && tmp->type == T_CHARACTER)
	{
		i++;
		tmp = tmp->next;
	}
	return i;
}

void stock_string_token(t_data *data)
{
    t_list  *cursor = data->lst;
	t_token	*buffer;
	char	tmp[2];

	data->token = NULL;
    while (cursor)
    {
        if (cursor->type == T_DOUBLE_QUOTE)
            handle_and_store_token(data, &cursor, T_DOUBLE_QUOTE, T_WORD_DOUBLE_QUOTE);
        else if (cursor->type == T_SIMPLE_QUOTE)
            handle_and_store_token(data, &cursor, T_SIMPLE_QUOTE, T_WORD_SIMPLE_QUOTE);
        else if (cursor->type == T_DOLLAR && cursor->next && cursor->next->type == T_CHARACTER)
            handle_and_store_token(data, &cursor, T_DOLLAR, T_EXPAND);
        else if (cursor->type == T_CHARACTER)
            handle_and_store_token(data, &cursor, T_CHARACTER, T_WORD);
        else
        {
			tmp[0] = cursor->character;
			tmp[1] = '\0';
            buffer = ft_lstnew_token(tmp, token_for_symbol(tmp[0]));
			ft_lstadd_back_token(&data->token, buffer);
            cursor = cursor->next;
        }
    }
}

void handle_and_store_token(t_data *data, t_list **cursor, int type, int token_type)
{
    t_token *buffer;

    if (type == T_DOUBLE_QUOTE || type == T_SIMPLE_QUOTE)
        handle_quote(data, cursor, type);
    else if (type == T_DOLLAR)
        handle_dollar(data, cursor);
    else if (type == T_CHARACTER)
        handle_character(data, cursor);
    else
        return;
    buffer = ft_lstnew_token(data->str_stock_lst, token_type);
    if (!buffer)
    {
        fprintf(stderr, "Error: Failed to allocate memory for token\n");
        free(data->str_stock_lst);
        return;
    }
    ft_lstadd_back_token(&data->token, buffer);
    free(data->str_stock_lst);
    data->str_stock_lst = NULL;
}
