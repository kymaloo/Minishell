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

	before = string_len_before_expand(str);
	after = string_len_after_expand(str);
	if (data->expand == NULL)
		between = 0;
	else
		between = ft_strlen(data->expand);
	printf("%s\n", data->expand);
	if (data->expand == NULL && before == 0 && after == 0)
		return (NULL);
	else if (data->expand != NULL && before != 0 && after != 0)
		result = regroup_all_expand(data, str, 0, 0);
	// else if (data->expand != NULL && before != 0 && after == 0)
	// 	result = regroup_before_and_between_expand(data);
	// else if (data->expand != NULL && before == 0 && after != 0)
	// 	result = regroup_after_and_between_expand(data);
	else
		result = ft_strdup(data->expand);
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
	result = malloc(sizeof(char) * the_string_length_in_the_double_quote_with_expand_change(data, str) + 1);
	while (before[i])
		result[j++] = before[i++];
	i = 0;
	while (between[i])
		result[j++] = between[i++];
	i = 0;
	while (after[i])
		result[j++] = after[i++];
	result[j] = '\0';
	return (result);
}
