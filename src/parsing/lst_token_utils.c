#include "../include/minishell.h"

void	print_lst_token(t_data *data, int identifier)
{
	t_token	*cursor;

	if (identifier == TOKEN)
		cursor = data->token;
	else
		cursor = data->tmp;
	if (!cursor)
	{
		printf("Token list is empty.\n");
		return ;
	}
	while (cursor)
	{
		printf("Character: %s  Token: %d\n", cursor->character, cursor->type);
		cursor = cursor->next;
	}
	printf("\n");
}

void	destroy_node_token(t_token *token)
{
	if (token == NULL)
		return ;
	if (token->character != NULL)
	{
		free(token->character);
	}
	free(token);
}

void	ft_lstclear_tmp(t_token **tmp)
{
	t_token	*tmp3;
	t_token	*tmp2;

	if (!tmp)
		return ;
	tmp3 = *tmp;
	while (tmp3)
	{
		tmp2 = tmp3->next;
		free(tmp3->character);
		free(tmp3);
		tmp3 = tmp2;
	}
	*tmp = NULL;
}
