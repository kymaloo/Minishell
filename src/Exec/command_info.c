
#include "../../include/minishell.h"

void	print_command_info(t_token *tokens)
{
	t_token	*cursor;

	if (!tokens)
	{
		printf("No command found.\n");
		return ;
	}
	printf("Command and Arguments:\n");
	cursor = tokens;
	while (cursor)
	{
		printf("Token: %s, Type: %d\n", cursor->character, cursor->type);
		cursor = cursor->next;
	}
}
