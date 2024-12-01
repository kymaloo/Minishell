#include "../include/minishell.h"

void	print_lst(t_data *data)
{
	t_list		*cursor;

	cursor = data->lst;
	if (cursor == NULL)
		return ;
	while (cursor != NULL)
	{
		printf("Character: %c  Token: %d\n", cursor->character, cursor->type);
		cursor = cursor->next;
	}
	printf("\n");
}
