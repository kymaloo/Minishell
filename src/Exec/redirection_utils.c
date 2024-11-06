/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aafounas <aafounas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 17:09:42 by aafounas          #+#    #+#             */
/*   Updated: 2024/11/06 17:46:54 by aafounas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void handle_output_redirection(char **cmd, int *stdout_backup, int i)
{
    int fd;

    fd = open(cmd[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) 
	{
        perror("open");
        return;
    }
    *stdout_backup = dup(1);
    dup2(fd, 1);
    close(fd);
    cmd[i] = NULL;
}

void handle_input_redirection(char **cmd, int *stdin_backup, int i)
{
    int fd;

    fd = open(cmd[i + 1], O_RDONLY);
    if (fd == -1) 
	{
        perror("open");
        return;
    }
    *stdin_backup = dup(0);
    dup2(fd, 0);
    close(fd);
    cmd[i] = NULL;
}

void handle_redirection(char **cmd, int *stdin_backup, int *stdout_backup)
{
    int i;

    i = 0;
    while (cmd[i]) 
	{
        if (ft_strncmp(cmd[i], ">", 2) == 0 && cmd[i + 1]) 
		{
            handle_output_redirection(cmd, stdout_backup, i);
            break;
        }
		else if (ft_strncmp(cmd[i], "<", 2) == 0 && cmd[i + 1]) 
		{
            handle_input_redirection(cmd, stdin_backup, i);
            break;
        }
        i++;
    }
}

void restore_redirection(int stdin_backup, int stdout_backup)
{
    if (stdin_backup != -1) 
	{
        dup2(stdin_backup, 0);
        close(stdin_backup);
    }
    if (stdout_backup != -1) 
	{
        dup2(stdout_backup, 1);
        close(stdout_backup);
    }
}