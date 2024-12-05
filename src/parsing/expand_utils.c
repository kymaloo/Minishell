#include "../include/minishell.h"

void	replace_expand_in_double_quote(t_data *data)
{
    t_token *cursor;

	cursor = data->token;
    while (cursor)
    {
        if (cursor->type == T_WORD_DOUBLE_QUOTE)
        {
            handle_double_quote(cursor, data);
        }
        cursor = cursor->next;
    }
}

void	handle_double_quote(t_token *cursor, t_data *data)
{
	char *str;

    if (check_dollar_in_double_quote(cursor->character) == 0)
    {
        str = extract_content_between_quotes(cursor->character);
        stock_str_in_lst(data, str);
		free(str);
        stock_string_token(data, TMP);
        ft_lstclear(&data->lst);
        replace_expand(data, TMP);
        free(cursor->character);
        cursor->character = stock_all_character_lst(data);
        ft_lstclear_tmp(&data->tmp);
    }
}

char	*extract_content_between_quotes(char *str)
{
    int i;
	int	j;
    char *result;

	i = 0;
	j = 1;
	result = malloc(ft_strlen(str) - 1);
    while (str[j] && str[j] != '"')
    {
        result[i] = str[j];
        i++;
        j++;
    }
    result[i] = '\0';
    return result;
}

int	count_all_character_lst(t_data *data)
{
	t_token	*cursor;
	int	i;
	int	j;

	cursor = data->tmp;
	i = 0;
	j = 0;
	while (cursor)
	{
		i = i + ft_strlen(cursor->character);
		j++;
		cursor = cursor->next;
	}
	j--;
	return (i);
}

char	*stock_all_character_lst(t_data *data)
{
	t_token	*cursor;
	char	*result;
	int		i;
	int		j;

	cursor = data->tmp;
	i = count_all_character_lst(data);
	result = malloc(sizeof(char) * i + 1);
	i = 0;
	j = 0;
	while (cursor)
	{
		while (cursor->character[i])
		{
			result[j] = cursor->character[i];
			j++;
			i++;
		}
		i = 0;
		cursor = cursor->next;
	}
	result[j] = '\0';
	return (result);
}
