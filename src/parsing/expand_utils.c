#include "../include/minishell.h"

void	replace_expand_in_double_quote(t_data *data)
{
    t_token *cursor;
	char	*str;
	int		i;
	int		count;

	i = 0;
	cursor = data->token;
    while (cursor)
    {
        if (cursor->type == T_WORD_DOUBLE_QUOTE)
        {
			str = extract_content_between_quotes(cursor->character);
			count = count_number_expand_in_double_quote(str);
			while (i != count)
			{
            	handle_double_quote(cursor, data);
				i++;
			}
			//boucle pour verifier s'il y a encore un expand
        }
        cursor = cursor->next;
    }
}

void	handle_double_quote(t_token *cursor, t_data *data)
{
	char *str;
	char *expand;

    if (check_dollar_in_double_quote(cursor->character) == 0)
    {
		str = extract_content_between_quotes(cursor->character);
		stock_string_before_expand(str);
		expand = stock_string_between_expand(str);
		stock_string_after_expand(str);
        stock_str_in_lst(data, expand);
		free(expand);
        stock_string_token(data, TMP);
        ft_lstclear(&data->lst);
        replace_expand(data, TMP);
		count_number_expand_in_double_quote(str);
		the_string_length_in_the_double_quote_with_expand_change(data, str);
		expand = regroup_str_in_the_double_quote_with_expand_change(data, str);
		free(str);
        free(cursor->character);
		cursor->character = ft_strdup(expand);
		free(data->expand);
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
		if(cursor->character)
		{
			i = i + ft_strlen(cursor->character);
			j++;
		}
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
		while (cursor->character && cursor->character[i])
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

