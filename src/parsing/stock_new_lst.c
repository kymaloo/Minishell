#include "../include/minishell.h"

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

// Recupere les caracteres de la liste chainer "lst" pour les mettres dans une t_token en regrouper les cararteres en 5 categorie
// - Les mots "T_WORD"
// - Les expands "T_EXPAND"
// - Les caracters entre simple quote "T_WORD_SIMPLE_QUOTE"
// - Les caracters entre simple quote "T_WORD_DOUBLE_QUOTE"
// - Les symboles "|<> " 

void	stock_string_token(t_data *data, int identifier)
{
	t_list	*cursor;

	if (identifier == TOKEN)
		data->token = NULL;
	else
		data->tmp = NULL;
	cursor = data->lst;
	while (cursor)
	{
		if (cursor->type == T_DOUBLE_QUOTE)
			handle_and_store_token(data, &cursor, T_DOUBLE_QUOTE, T_WORD_DOUBLE_QUOTE, identifier);
		else if (cursor->type == T_SIMPLE_QUOTE)
			handle_and_store_token(data, &cursor, T_SIMPLE_QUOTE, T_WORD_SIMPLE_QUOTE, identifier);
		else if (cursor->type == T_DOLLAR && cursor->next && cursor->next->type == T_CHARACTER)
			handle_and_store_token(data, &cursor, T_DOLLAR, T_EXPAND, identifier);
		else if (cursor->type == T_CHARACTER)
			handle_and_store_token(data, &cursor, T_CHARACTER, T_WORD, identifier);
		else
			handle_symbol_token(data, &cursor, identifier);
	}
}

void	handle_symbol_token(t_data *data, t_list **cursor, int identifier)
{
	char	tmp[2];
	t_token	*buffer;

	tmp[0] = (*cursor)->character;
	tmp[1] = '\0';
	buffer = ft_lstnew_token(tmp, token_for_symbol(tmp[0]));
	if (!buffer)
	{
		free(data->str_stock_lst);
		data->str_stock_lst = NULL;
		return ;
	}
	if (identifier == TOKEN)
		ft_lstadd_back_token(&data->token, buffer);
	else
		ft_lstadd_back_token(&data->tmp, buffer);
	*cursor = (*cursor)->next;
}

void	handle_and_store_token(t_data *data, t_list **cursor, int type, int tk, int identifier)
{
	t_token	*buffer;

	if (type == T_DOUBLE_QUOTE || type == T_SIMPLE_QUOTE)
		handle_quote(data, cursor, type);
	else if (type == T_DOLLAR)
		handle_dollar(data, cursor);
	else if (type == T_CHARACTER)
		handle_character(data, cursor);
	else
		return ;
	buffer = ft_lstnew_token(data->str_stock_lst, tk);
	if (!buffer)
	{
		free(data->str_stock_lst);
		data->str_stock_lst = NULL;
		return ;
	}
	if (identifier == TOKEN)
		ft_lstadd_back_token(&data->token, buffer);
	else
		ft_lstadd_back_token(&data->tmp, buffer);
	free(data->str_stock_lst);
	data->str_stock_lst = NULL;
}
