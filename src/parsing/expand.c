#include "../include/minishell.h"

char	*recup_expand(t_data *data, int identifier)
{
	t_token	*cursor;
	char	*result;
	int		i;
	int		j;

	if (identifier == TOKEN)
		cursor = data->token;
	else
		cursor = data->tmp;
	i = 0;
	j = 1;
	while (cursor)
	{
		if (cursor->type == T_EXPAND)
		{
			result = malloc(sizeof(char) * ft_strlen(cursor->character) + 1);
			while (cursor->character[j])
			{
				result[i] = cursor->character[j];
				i++;
				j++;
			}
			result[i++] = '=';
			result[i] = '\0';
			return (result);
		}
		cursor = cursor->next;
	}
	return (NULL);
}

char	*recup_var_env(t_data *data, int identifier)
{
	int		i;
	int		j;
	int		k;
	int		tmp;
	char	*result;

	i = 0;
	j = 0;
	k = 0;
	if (identifier == TOKEN)
		result = recup_expand(data, TOKEN);
	else
		result = recup_expand(data, TMP);
	while(data->env_copy[i] && strncmp(result, data->env_copy[i], ft_strlen(result)) != 0)
		i++;
	if (data->env_copy[i] == NULL)
		return (NULL);
	j = ft_strlen(result);
	tmp = ft_strlen(&data->env_copy[i][j]);
	free(result);
	result = malloc(sizeof(char) * tmp + 1);
	while (data->env_copy[i][j])
		result[k++] = data->env_copy[i][j++];
	result[k] = '\0';
	return (result);
}

void replace_expand(t_data *data, int identifier)
{
    t_token *cursor;

    if (identifier == TOKEN)
        cursor = data->token;
    else
        cursor = data->tmp;
    while (cursor)
    {
        if (cursor->type == T_EXPAND)
            process_expansion(data, identifier, cursor);
        cursor = cursor->next;
    }
}

void process_expansion(t_data *data, int identifier, t_token *cursor)
{
    char *result = recup_var_env(data, identifier);
    if (result == NULL)
    {
        handle_expansion_failure(data, identifier, cursor);
		data->expand = NULL;
        return ;
    }
    update_token(cursor, TOKEN, result);
	data->expand = ft_strdup(cursor->character);
    free(result);
}

void handle_expansion_failure(t_data *data, int identifier, t_token *cursor)
{
    if (identifier == TOKEN)
        free_node_token(&data->token, cursor);
    else
        free_node_token(&data->tmp, cursor);
}

void update_token(t_token *cursor, int identifier, char *result)
{
    free(cursor->character);
	if (identifier == TOKEN && ft_isalnum(result[0]) == 0)
	 	cursor->character  = check_white_space_expand_in_double_quote(result);
	else
    	cursor->character = ft_strdup(result);
    cursor->type = T_WORD;
}

char	*check_white_space_expand_in_double_quote(char *str)
{
	int		len;
	int		i;
	int		j;
	char	*result;

	len = ft_strlen(str);
	i = 0;
	if (ft_isalnum(str[0]) != 0)
		return (str);
	while (ft_isalnum(str[i]) == 0)
		i++;
	j = i;
	i = len - i;
	result = malloc(sizeof(char) * i + 1);
	if (!result)
	{
		free(str);
		return (NULL);
	}
	i = 0;
	while (str[j])
		result[i++] = str[j++];
	result[i] = '\0';

	return (result);
}

int check_dollar_in_double_quote(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			if (ft_isalnum(str[i + 1]) != 0)
				return (0);
		}
		i++;
	}
	return (1);
}

void	free_node_token(t_token **head, t_token *target)
{
	t_token	*current;
	t_token	*tmp;

    if (head == NULL || *head == NULL || target == NULL)
		return ;
	current = *head;
    if (current == target && current->next == NULL)
	{
		free((*head)->character);
        free(*head);
		*head = NULL;
		return ;
	}
	if (current == target)
	{
		free((*head)->character);
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
		free(target->character);
		target->character = NULL;
        free(target);
		target = NULL;
    }
}
