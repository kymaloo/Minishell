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
			result = malloc(sizeof(char) * ft_strlen(cursor->character));
			while (cursor->character[j])
			{
				result[i] = cursor->character[j];
				i++;
				j++;
			}
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
	{
		i++;
	}
	if (data->env_copy[i] == NULL)
		return (NULL);
	j = ft_strlen(result) + 1;
	tmp = ft_strlen(&data->env_copy[i][j]);
	free(result);
	result = malloc(sizeof(char) * tmp + 1);
	while (data->env_copy[i][j])
	{
		result[k] = data->env_copy[i][j];
		j++;
		k++;
	}
	result[k] = '\0';
	return (result);
}

void	replace_expand(t_data *data, int identifier)
{
	t_token	*cursor;
	char	*result;
	int		i;

	if (identifier == TOKEN)
		cursor = data->token;
	else
		cursor = data->tmp;
	i = 0;
	while (cursor)
	{
		if (cursor->type == T_EXPAND)
		{
			result = recup_var_env(data, identifier);
			if (result == NULL)
			{
				free(result);
				//Free node
				return ;
			}
			free(cursor->character);
			cursor->character = ft_strdup(result);
			free(result);
			cursor->type = T_WORD;
		}
		i++;
		cursor = cursor->next;
	}
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
