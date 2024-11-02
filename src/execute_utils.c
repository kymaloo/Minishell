/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aafounas <aafounas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 17:11:33 by aafounas          #+#    #+#             */
/*   Updated: 2024/11/02 17:13:13 by aafounas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	error(char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

void	execute_basic(char *argv, char **envp)
{
	char	**cmd;
	int		i;
	char	*path;

	i = 0;
	cmd = ft_split(argv, ' ');
	if (!cmd)
		error("split failed");
	path = find_path(cmd[0], envp);
	if (!path || execve(path, cmd, envp) == -1)
	{
		while (cmd[i])
			free(cmd[i++]);
		free(cmd);
		error("execution failed");
	}
}

void execute(char *argv, char **envp)
{
    char **cmd;
    int stdin_backup;
    int stdout_backup;

    stdin_backup = -1;
    stdout_backup = -1;
    cmd = ft_split(argv, ' ');
    if (!cmd) 
    {
        perror("split failed");
        return;
    }
    handle_redirection(cmd, &stdin_backup, &stdout_backup);
    prepare_command_execution(cmd, envp);
    free_array(cmd);
    restore_redirection(stdin_backup, stdout_backup);
}
