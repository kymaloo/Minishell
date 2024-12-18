#include "../include/minishell.h"

void	free_node_lst(t_list **head, t_list *target)
{
    t_list *current;
    t_list *tmp;

    if (head == NULL || *head == NULL || target == NULL)
		return ;
    current = *head;
    if (current == target && current->next == NULL)
    {
        free(*head);
        *head = NULL;
        return;
    }
    if (current == target)
    {
        *head = current->next;
        free(target);
		return ;
    }
    while (current != NULL && current != target)
    {
        tmp = current;
        current = current->next;
    }
    if (current)
    {
        if (!current->next)
            tmp->next = NULL;
        else
            tmp->next = current->next;

        free(target);
        target = NULL;
    }
}

int	string_len_before_expand(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '$')
		i++;
	return (i);
}

char	*stock_string_before_expand(char *str)
{
	int	i;
	int	j;
	char	*result;

	i = 0;
	j = string_len_before_expand(str);
	if (j == 0)
		return (NULL);
	result = malloc(sizeof(char) * j + 1);
	while (i != j)
	{
		result[i] = str[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

int	string_len_between_expand(char *str)
{
	int	i;
	int	j;

	i = 0;
	while (str[i] && str[i] != '$')
		i++;
	if (str[i] == '\0')
		return (0);
	j = 1;
	i++;
	while (str[i] && (ft_isalpha(str[i]) != 0 || str[i] == '_'))
	{
		i++;
		j++;
	}
	return (j);
}

char	*stock_string_between_expand(char *str)
{
	int		i;
	int		j;
	char	*result;

	i = 0;
	j = string_len_between_expand(str);
	result = malloc(sizeof(char) * j + 1);
	while (str[i] && str[i] != '$')
		i++;
	j = 0;
	result[j] = str[i];
	i++;
	j++;
	while (str[i] && (ft_isalpha(str[i]) != 0 || str[i] == '_'))
	{
		result[j] = str[i];
		i++;
		j++;
	}
	result[j] = '\0';
	return (result);
}

int	string_len_after_expand(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] && str[i] != '$')
		i++;
	i++;
	while (str[i] && (ft_isalpha(str[i]) != 0 || str[i] == '_'))
		i++;
	if (str[i] == '\0')
		return (0);
	while (str[i])
	{
		i++;
		j++;
	}
	return (j);
}

char	*stock_string_after_expand(char *str)
{
	int	i;
	int	j;
	char	*result;

	i = 0;
	j = string_len_after_expand(str);
	if (j == 0)
		return (NULL);
	result = malloc(sizeof(char) * j + 1);
	//if (!result)
	while (str[i] && str[i] != '$')
		i++;
	i++;
	while (str[i] && (ft_isalpha(str[i]) != 0 || str[i] == '_'))
		i++;
	if (str[i] == '\0')
		return (0);
	j = 0;
	while (str[i])
	{
		result[j] = str[i];
		i++;
		j++;
	}
	result[j] = '\0';
	return (result);
}

int	count_number_expand_in_double_quote(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '$' && ft_isalnum(str[i + 1]) != 0)
		{
			count++;
			i += 2;
		}
		i++;
	}
	return (count);
}

int	the_string_length_in_the_double_quote_with_expand_change(t_data *data, char *str)
{
	int	before;
	int	between;
	int	after;

	before = string_len_before_expand(str);
	after = string_len_after_expand(str);
	if (data->expand == NULL)
		between = 0;
	else
		between = ft_strlen(data->expand);
	if (data->expand == NULL && before == 0 && after == 0)
		return (0);
	else if (data->expand != NULL && before != 0 && after != 0)
		return (before + between + after);
	else if (data->expand != NULL && before != 0 && after == 0)
		return (before + between);
	else
		return (between + after);
}

char	*regroup_str_in_the_double_quote_with_expand_change(t_data *data, char *str)
{
	int		before;
	int		between;
	int		after;
	char	*result;

	result = NULL;

	before = string_len_before_expand(str);
	after = string_len_after_expand(str);
	if (data->expand == NULL && before == 0 && after == 0)
		return (NULL);
	if (data->expand == NULL)
		between = 0;
	else
		between = ft_strlen(data->expand);
	if (data->expand != NULL && before != 0 && after != 0)
		result = regroup_all_expand(data, str, 0, 0);
	else if (data->expand != NULL && before != 0 && after == 0)
		result = regroup_before_and_between_expand(data, str, 0, 0);
	else if (data->expand != NULL && before == 0 && after != 0)
		result = regroup_after_and_between_expand(data, str, 0, 0);
	else if (data->expand != NULL)
		result = ft_strdup(data->expand);
	else if (data->expand == NULL && before != 0 && after != 0)
		result = regroup_before_and_after_expand(data, str, 0, 0);
	else if (data->expand == NULL && before == 0 && after != 0)
		result = stock_string_after_expand(str);
	else
		result = stock_string_before_expand(str);
	return (result);
}

char	*regroup_all_expand(t_data *data, char *str, int i, int j)
{
	char	*before;
	char	*between;
	char	*after;
	char	*result;

	before = stock_string_before_expand(str);
	between = ft_strdup(data->expand);
	after = stock_string_after_expand(str);
	result = malloc(sizeof(char) * the_string_length_in_the_double_quote_with_expand_change(data, str) + 3);
	result[j] = '"';
	j++;
	while (before[i])
		result[j++] = before[i++];
	i = 0;
	while (between[i])
		result[j++] = between[i++];
	i = 0;
	while (after[i])
		result[j++] = after[i++];
	result[j] = '"';
	j++;
	result[j] = '\0';
	return (result);
}

char	*regroup_before_and_between_expand(t_data *data, char *str, int i, int j)
{
	char	*before;
	char	*between;
	char	*result;

	before = stock_string_before_expand(str);
	between = ft_strdup(data->expand);
	result = malloc(sizeof(char) * the_string_length_in_the_double_quote_with_expand_change(data, str) + 3);
	result[j] = '"';
	j++;
	while (before[i])
		result[j++] = before[i++];
	i = 0;
	while (between[i])
		result[j++] = between[i++];
	result[j] = '"';
	j++;
	result[j] = '\0';
	return (result);
}

char	*regroup_after_and_between_expand(t_data *data, char *str, int i, int j)
{
	char	*between;
	char	*after;
	char	*result;

	between = ft_strdup(data->expand);
	after = stock_string_after_expand(str);
	result = malloc(sizeof(char) * the_string_length_in_the_double_quote_with_expand_change(data, str) + 3);
	result[j] = '"';
	j++;
	while (between[i])
		result[j++] = between[i++];
	i = 0;
	while (after[i])
		result[j++] = after[i++];
	result[j] = '"';
	j++;
	result[j] = '\0';
	return (result);
}

char	*regroup_before_and_after_expand(t_data *data, char *str, int i, int j)
{
	char	*before;
	char	*after;
	char	*result;

	before = stock_string_before_expand(str);
	after = stock_string_after_expand(str);
	result = malloc(sizeof(char) * the_string_length_in_the_double_quote_with_expand_change(data, str) + 3);
	result[j] = '"';
	j++;
	while (before[i])
		result[j++] = before[i++];
	i = 0;
	while (after[i])
		result[j++] = after[i++];
	result[j] = '"';
	j++;
	result[j] = '\0';
	return (result);
}

void	detete_dollars_before_quote(t_data *data, int type)
{
	t_token	*cursor;
	t_token	**head;

	cursor = data->token;
	head = &data->token;
	while (cursor)
	{
		if (cursor->type == T_DOLLAR)
		{
			if (cursor->next && cursor->next->type == type)
				free_node_token(head, cursor);
		}
		cursor = cursor->next;
	}	
}

void	delete_all_consecutive(t_data *data, int type)
{
    t_list *cursor;
	t_list *tmp;
    t_list **head;

    cursor = data->lst;
    head = &data->lst;
    while (cursor && cursor->next)
    {
        if (cursor->type == type && cursor->next->type == type)
        {
			tmp = cursor->next;
            free_node_lst(head, cursor);
            free_node_lst(head, tmp);
            cursor = *head;
        }
		else
        	cursor = cursor->next;
    }
}

void	merge_token(t_data *data, int type1, int type2)
{
	t_token	*cursor;
	t_token	*tmp;
	t_token	**head;
	char	*str1;
	char	*str2;
	char	*result;

	cursor = data->token;
	head = &data->token;
	while (cursor && cursor->next)
	{
		if (cursor->type == type1 && cursor->next->type == type2)
		{
			str1 = stock_merge_token(cursor->character, type1);
			str2 = stock_merge_token(cursor->next->character, type2);
			result = strdup_cat(str1, str2);
			//printf("%s\n", result);
			free(str1);
			free(str2);
			cursor->next->character = result;
			cursor->next->type = T_WORD_MERGE;
			//free(result);
            //*head = cursor;
			tmp = cursor;
            cursor = cursor->next;
            free_node_token(head, tmp);
		}
		else
			cursor = cursor->next;
	}
}

int	len_merge_token(char *str1, char *str2, int type1, int type2)
{
	int	i;
	int	j;
	int	result;

	i = ft_strlen(str1);
	j = ft_strlen(str2);
	if (type1 == T_WORD_SIMPLE_QUOTE || type1 == T_WORD_DOUBLE_QUOTE)
		i = i - 2;
	if (type2 == T_WORD_SIMPLE_QUOTE || type2 == T_WORD_DOUBLE_QUOTE)
		j = j - 2;
	result = i + j;
	return (result);
}

char	*stock_merge_token(char *str, int type)
{
	int		i;
	int		j;
	int		len;
	char	*result;

	if (type == T_WORD_SIMPLE_QUOTE || type == T_WORD_DOUBLE_QUOTE)
	{
		len = ft_strlen(str) - 2;
		i = 1;
	}
	else
	{
		len = ft_strlen(str);
		i = 0;
	}
	result = malloc(sizeof(char) * len + 1);
	if (!result)
	{
		free(str);
		return (NULL);
	}
	j = 0;
	while (j != len)
		result[j++] = str[i++];
	result[j] = '\0';
	printf("%s\n", result);
	return (result);
}

char	*strdup_cat(char *str1, char *str2)
{
	char	*result;
	int		i;
	int		j;

	i = ft_strlen(str1) + ft_strlen(str2);
	result = malloc(sizeof(char) * i + 1);
	if (!result)
	{
		free(str1);
		free(str2);
		return (NULL);
	}
	i = 0;
	j = 0;
	while (str1[i])
		result[j++] = str1[i++];
	i = 0;
	while (str2[i])
		result[j++] = str2[i++];
	result[j] = '\0';
	printf("%s\n", result);
	return (result);
}

