
#include "../../include/minishell.h"

void	print_command_info(t_command_node *node)
{
	int	i;

	i = 0;
	printf("Command: %s\n", node->cmd);
	printf("Arguments:\n");
	while (i < node->arg_count)
	{
		printf("[%d]: %s\n", i, node->args[i]);
		i++;
	}
}
