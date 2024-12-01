#include "../include/minishell.h"

void	handle_quote(t_data *data, t_list **cursor, int type)
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

void	handle_dollar(t_data *data, t_list **cursor)
{
	int		i;
	t_list	*start;

	i = count_handle_dollar(*cursor);
	data->str_stock_lst = malloc(sizeof(char) * (i + 1));
	if (!data->str_stock_lst)
		return ;
	start = *cursor;
	i = 0;
	data->str_stock_lst[i++] = start->character;
	start = start->next;
	while (start && start->type == T_CHARACTER)
	{
		data->str_stock_lst[i++] = start->character;
		start = start->next;
	}
	data->str_stock_lst[i] = '\0';
	*cursor = start;
}

void	handle_character(t_data *data, t_list **cursor)
{
	int		i;
	t_list	*start;

	i = count_handle_character(*cursor);
	data->str_stock_lst = malloc(sizeof(char) * (i + 1));
	if (!data->str_stock_lst)
		return ;
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

int	count_handle_dollar(t_list *cursor)
{
	t_list	*tmp;
	int		i;

	if (!cursor || cursor->type != T_DOLLAR)
		return (0);
	tmp = cursor;
	i = 1;
	tmp = tmp->next;
	while (tmp && tmp->type == T_CHARACTER)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

int	count_handle_character(t_list *cursor)
{
	t_list	*tmp;
	int		i;

	if (!cursor || cursor->type != T_CHARACTER)
		return (0);
	tmp = cursor;
	i = 0;
	while (tmp && tmp->type == T_CHARACTER)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}
