#include "../include/minishell.h"

void	detete_dollars_before_quote(t_data *data, int type)
{
	t_token	*cursor;

	cursor = data->token;
	while (cursor)
	{
		if (cursor && cursor->type == T_DOLLAR)
		{
			if (cursor->next->type == type)
			{
				free_node_token(&data->token, cursor);
			}
		}
		cursor = cursor->next;
	}
}

void	delete_two_quote_consecutiv(t_list *lst, int type)
{
	t_list	*cursor;

	if (!lst)
		return ;
	cursor = lst;
	while (cursor)
	{
		if (cursor && cursor->type == type)
		{
			if (cursor->next && cursor->next->type == type)
			{
				free_node_lst(&lst, cursor);
				cursor = cursor->next;
				free_node_lst(&lst, cursor);
				if (!lst || !cursor || cursor->next == NULL)
					return ;
			}
		}
		else
			cursor = cursor->next;
	}
}

void	free_node_lst(t_list** head, t_list* target)
{
	t_list	*current;
	t_list	*tmp;

    if (head == NULL || *head == NULL || target == NULL)
	{
        return ;
	}
	current = *head;
    if (current == target)
	{
        free(*head);
		*head = NULL;
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

char	*stock_string_before_expand(char *str)
{
	int		i;
	char	*result;

	i = 0;
	while (str[i] && str[i] != '$')
		i++;
	result = malloc(sizeof(char) * i + 1);
	if (!result)
	{
		free(str);
		return (NULL);
	}
	i = 0;
	while (str[i] && str[i] != '$')
	{
		result[i] = str[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

char	*stock_string_between_expand(char *str)
{
	int		i;
	int		j;
	int		tmp;
	int		before;
	char	*result;

	i = 0;
	j = 0;
	before = 0;
	while (str[i] && str[i] != '$')
	{
		before++;
		i++;
	}
	i++;
	tmp = i;
	while (str[i] && ft_isalnum(str[i]) != 0)
		i++;
	result = malloc(sizeof(char) * (i - before + 1));
	if (!result)
	{
		free(str);
		return (NULL);
	}
	result[j] = str[tmp - 1];
	j++;
	while (str[tmp] && (ft_isalnum(str[tmp]) != 0 || str[tmp] == '$'))
	{
		
		result[j] = str[tmp];
		tmp++;
		j++;
	}
	result[j] = '\0';
	return (result);
}

char	*stock_string_after_expand(char *str)
{
	int	i;
	int	j;
	int	after;
	char	*result;

	i = 0;
	after = 0;
	while (str[i] && str[i] != '$')
		i++;
	i++;
	while (str[i] && ft_isalnum(str[i]) != 0)
		i++;
	j = i;
	while (str[i])
	{
		i++;
		after++;
	}
	result = malloc(sizeof(char) * (i - after + 1));
	if (!result)
	{
		free(str);
		return (NULL);
	}
	i = 0;
	while (str[j])
	{
		result[i] = str[j];
		i++;
		j++;
	}
	result[i] = '\0';
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
		if (str[i] && ft_isalnum(str[i + 1]) == 0)
		{
			count++;
			i += 2;
		}
		i++;
	}
	//printf("%d\n", count);
	return (count);
}

int	the_string_length_in_the_double_quote_with_expand_change(t_data *data, char *str)
{
	int	count;

	count = ft_strlen(stock_string_before_expand(str)) + ft_strlen(stock_string_after_expand(str)) + ft_strlen(data->expand) - 3;
	printf("%d\n", count);
	return (count);
}

char	*regroup_str_in_the_double_quote_with_expand_change(t_data *data, char *str)
{
	char *result;
	char *before;
	char *after;
	int	i;
	int	j;

	i = 0;
	j = 0;
	before = stock_string_before_expand(str);
	after = stock_string_after_expand(str);
	if (ft_strlen(stock_string_before_expand(str)) <= 0 && ft_strlen(stock_string_after_expand(str)) <= 0)
		result = ft_strdup(data->expand);
	result = malloc(sizeof(char) * the_string_length_in_the_double_quote_with_expand_change(data, str) + 1);
	if (ft_strlen(stock_string_after_expand(str)) <= 0)
	{
		while(before[i])
		{
			result[j] = before[i];
			j++;
			i++;
		}
		i = 0;
		while (data->expand[i])
		{
			result[j] = data->expand[i];
			i++;
			j++;
		}
		result[j] = '\0';
	}
	else if (ft_strlen(stock_string_before_expand(str)) <= 0)
	{
		i = 0;
		while (data->expand[i])
		{
			result[j] = data->expand[i];
			i++;
			j++;
		}
		i = 0;
		while(after[i])
		{
			result[j] = after[i];
			j++;
			i++;
		}
		result[j] = '\0';
	}
	else
	{
		while(before[i])
		{
			result[j] = before[i];
			j++;
			i++;
		}
		i = 0;
		while (data->expand[i])
		{
			result[j] = data->expand[i];
			i++;
			j++;
		}
		i = 0;
		while(after[i])
		{
			result[j] = after[i];
			j++;
			i++;
		}
		result[j] = '\0';
	}
	return (result);
}
