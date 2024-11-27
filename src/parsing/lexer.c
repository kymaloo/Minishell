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
		printf("Character: %c, Token: %d\n", cursor->character, cursor->type);
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
