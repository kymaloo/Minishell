#include "../include/minishell.h"

int	count_regroup_symbole(t_token *token, int type)
{
	t_token	*cursor;
	int		i;

	cursor = token;
	i = 0;
	while (cursor && cursor->type != type)
	{
		if (!cursor || !cursor->next)
			return (i);
		cursor = cursor->next;
	}
	while (cursor && cursor->type == type)
	{
		i++;
		cursor = cursor->next;
	}
	return (i);
}

void	regroup_symbole(t_token *token, char c, int type)
{
	t_token	*cursor;
	char	*result;
	int		i;
	int		count;

	count = count_regroup_symbole(token, type);
	if (count < 2)
		return ;
	cursor = token;
	i = 0;
	result = malloc(sizeof(char) * count + 1);
	while (cursor && cursor->type != type)
	{
		if (!cursor || !cursor->next)
			return ;
		cursor = cursor->next;
	}
	free(cursor->character);
	while (i != count)
	{
		result[i] = c;
		i++;
	}
	result[i] = '\0';
	cursor->character = ft_strdup(result);
	free(result);
	i = 1;
	cursor = cursor->next;
	while (i != count)
	{
		free_node_token(&token, cursor);
		i++;
		cursor = cursor->next;
	}
}
