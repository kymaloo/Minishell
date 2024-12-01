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

void	stock_string_token(t_data *data)
{
	t_list	*cursor;

	data->token = NULL;
	cursor = data->lst;
	while (cursor)
	{
		if (cursor->type == T_DOUBLE_QUOTE)
			handle_and_store_token(data, &cursor, T_DOUBLE_QUOTE, \
				T_WORD_DOUBLE_QUOTE);
		else if (cursor->type == T_SIMPLE_QUOTE)
			handle_and_store_token(data, &cursor, T_SIMPLE_QUOTE, \
				T_WORD_SIMPLE_QUOTE);
		else if (cursor->type == T_DOLLAR && cursor->next \
			&& cursor->next->type == T_CHARACTER)
			handle_and_store_token(data, &cursor, T_DOLLAR, T_EXPAND);
		else if (cursor->type == T_CHARACTER)
			handle_and_store_token(data, &cursor, T_CHARACTER, T_WORD);
		else
			handle_symbol_token(data, &cursor);
	}
}

void	handle_symbol_token(t_data *data, t_list **cursor)
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
	ft_lstadd_back_token(&data->token, buffer);
	*cursor = (*cursor)->next;
}

void	handle_and_store_token(t_data *data, t_list **cursor, int type, int tk)
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
	ft_lstadd_back_token(&data->token, buffer);
	free(data->str_stock_lst);
	data->str_stock_lst = NULL;
}
