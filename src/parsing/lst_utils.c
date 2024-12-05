#include "../include/minishell.h"

void	print_lst(t_data *data)
{
	t_list		*cursor;

	cursor = data->lst;
	if (!cursor)
	{
		printf("Token list is empty.\n");
		return ;
	}
	while (cursor)
	{
		printf("Character: %c  Token: %d\n", cursor->character, cursor->type);
		cursor = cursor->next;
	}
	printf("\n");
}
