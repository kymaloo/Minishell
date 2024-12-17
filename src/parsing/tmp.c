#include "../include/minishell.h"

void	free_node_lst(t_list** head, t_list* target)
{
	t_list	*current;
	t_list	*tmp;

    if (head == NULL || *head == NULL || target == NULL)
	{
        return ;
	}
	current = *head;
    if (current == target && current->next == NULL)
	{
        free(*head);
		*head = NULL;
		return ;
	}
	if (current == target)
	{
        free(*head);
		*head = current->next;
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

// void	delete_all_consecutive(t_data *data, int type)
// {
// 	t_list	*cursor;
// 	t_list	**head;

// 	cursor = data->lst;
// 	head = &data->lst;
// 	while (cursor)
// 	{
// 		if (cursor->type == type)
// 		{
// 			if (cursor->next)
// 			//{
// 				//free_node_lst(head, cursor);
// 			//}
// 				puts("test");
// 		}
// 		cursor = cursor->next;
// 	}	
// }
