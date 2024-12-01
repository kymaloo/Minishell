#include "../include/minishell.h"

void	print_lst_token(t_data *data)
{
	t_token	*cursor;

	cursor = data->token;
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
