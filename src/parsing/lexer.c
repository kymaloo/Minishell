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

	i = 0;
	while (data->input[i])
	{
		ft_lstadd_back(&data->lst, ft_lstnew(data->input[i], token_for_symbol(data->input[i])));
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
		printf("Character: %c, Token: %d\n", cursor->character[0], cursor->type);
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
/*
int	quote_is_pair(t_data *data)
{
	t_list		*cursor;
	t_token		*tmp;
	int			quote;
	int			double_quote;

	quote = 0;
	double_quote = 0;
	cursor = data->lst;
	if (cursor == NULL)
		return (1);
	while (cursor != NULL)
	{
		tmp = (t_token *)cursor->content;
		if (tmp->type == T_DOUBLE_QUOTE)
			double_quote++;
		if (tmp->type == T_SIMPLE_QUOTE)
			quote++;
		cursor = cursor->next;
	}
	if (quote % 2 != 0 || double_quote % 2 != 0)
		return (1);
	return (0);
}

void	transform_char(t_data *data, int token)
{
	t_list		*cursor;
	t_token		*tmp;
	int			cpt;

	cpt = 0;
	cursor = data->lst;
	if (cursor == NULL)
		return ;
	while (cursor != NULL)
	{
		tmp = (t_token *)cursor->content;
		if (cursor != NULL && cursor->next && tmp->type == token && cpt % 2 == 0)
		{
			if (tmp->type == token)
				cpt++;
			cursor = cursor->next;
			tmp = (t_token *)cursor->content;
			while (cursor != NULL && tmp->type != token)
			{		
				tmp->type = T_CHARACTER;
				cursor = cursor->next;
				if (cursor)
					tmp = (t_token *)cursor->content;
			}
		}
		else
			cursor = cursor->next;
	}
}

void	check_dollar(t_data *data, int token)
{
	t_list		*cursor;
	t_token		*tmp;
	int			cpt;

	cpt = 0;
	cursor = data->lst;
	if (cursor == NULL)
		return ;
	while (cursor != NULL)
	{
		tmp = (t_token *)cursor->content;
		if (cursor != NULL && cursor->next && tmp->type == token && cpt % 2 == 0)
		{
			if (tmp->type == token)
				cpt++;
			cursor = cursor->next;
			tmp = (t_token *)cursor->content;
			if (cursor != NULL && tmp->type != T_DOLLAR)
			{		
				tmp->type = T_CHARACTER;
				cursor = cursor->next;
				if (cursor)
					tmp = (t_token *)cursor->content;
			}
		}
		else
			cursor = cursor->next;
	}
}
*/