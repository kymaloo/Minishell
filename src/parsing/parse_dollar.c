#include "../include/minishell.h"

//Check si les quotes sont ferme en liste chainer

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

//Check si le dollars dans les doubles 
//quotes soit bien un dollars valide pour expand

void	check_dollar(t_data *data, int token, int cpt)
{
	t_list	*cursor;

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
			while (cursor && cursor->next && cursor->character == '$' \
				&& cursor->next->character == '$')
				cursor = cursor->next;
			if (cursor && cursor->next && cursor->next->type != T_WHITE_SPACE)
				cursor->type = T_DOLLAR;
		}
		else
			cursor = cursor->next;
	}
}

//Check s'il y a un dollar dans les doubles quotes
bool	is_dollar_in_double_quotes(t_data *data)
{
	bool	in_double_quotes;
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
