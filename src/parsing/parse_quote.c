#include "../include/minishell.h"

//Stock une string, characteres par characteres avec son token correspondent 

void	stock_str_in_lst(t_data *data, char *str)
{
	int			i;
	t_list		*buffer;

	i = 0;
	data->lst = NULL;
	while (str[i])
	{
		buffer = ft_lstnew(str[i], token_for_symbol(str[i]));
		ft_lstadd_back(&data->lst, buffer);
		i++;
	}
}

//Permet d'identifier le token du charactere

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

//Check si les quotes son fermer

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
		while (data->input[data->quote_is_paire] \
			&& data->input[data->quote_is_paire] != type)
			data->quote_is_paire++;
		if (data->input[data->quote_is_paire] == type)
			pair++;
		if (!data->input[data->quote_is_paire] && pair % 2 != 0)
			return (1);
	}
	return (0);
}

//Token : permet de savoir sur quelle quote agir
//Transform tous les tokens entre les quote en characters

void	transform_all_tokens_into_characters(t_data *data, int token)
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
