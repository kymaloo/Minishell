/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aafounas <aafounas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 14:55:33 by aafounas          #+#    #+#             */
/*   Updated: 2024/10/28 15:32:00 by aafounas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	run_command(char *input, char **envp)
{
	char	**cmd;
	int		i;

	i = 0;
	cmd = ft_split(input, ' ');
	if (!cmd || !cmd[0])
	{
		if (cmd)
			free_array(cmd);
		return ;
	}
	if (ft_strncmp(cmd[0], "exit", 5) == 0)
	{
		free_array(cmd);
		free(input);
		printf("exit\n");
		exit(0);
	}
	execute(input, envp);
	while (cmd[i])
	{
		free(cmd[i]);
		i++;
	}
	free(cmd);
}

int	main(int argc, char **argv, char **envp)
{
	char	*input;

	(void)argc;
	(void)argv;
	while (1)
	{
		input = readline("minishell$ ");
		if (input && *input)
		{
			add_history(input);
			run_command(input, envp);
		}
		free(input);
	}
	return (0);
}