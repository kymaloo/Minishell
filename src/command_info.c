/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aafounas <aafounas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 16:08:12 by aafounas          #+#    #+#             */
/*   Updated: 2024/11/02 17:13:43 by aafounas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
