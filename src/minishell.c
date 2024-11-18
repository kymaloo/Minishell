/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: r <r@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 14:55:33 by aafounas          #+#    #+#             */
/*   Updated: 2024/11/17 16:30:40 by r                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*void	run_command(char *input, char **envp)
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
}*/
void	run_command(char *input, char **envp)
{
	char	**args;

	args = ft_split(input, ' ');
	if (!args || !args[0])
	{
		if (args)
			free_array(args);
		return ;
	}
	if (is_builtin(args[0]))
		execute_builtin(args, envp);
	else
		execute(input, envp);
	free_array(args);
}


int	main(int argc, char **argv, char **envp)
{
	char	**env_copy;
	char	*input;

	(void)argc;
	(void)argv;

	env_copy = duplicate_env(envp);
	if (!env_copy)
	{
		perror("main: duplicate_env failed");
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		input = readline("minishell$ ");
		if (input && *input)
		{
			add_history(input);
			run_command(input, env_copy);
		}
		free(input);
	}
	free_array(env_copy);
	return (0);
}

