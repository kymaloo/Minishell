/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aafounas <aafounas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 16:08:12 by aafounas          #+#    #+#             */
/*   Updated: 2024/10/28 15:13:54 by aafounas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_command_info(t_command_node *node)
{
	int	i;

	i = 0;
	printf("Command: %s\n", node->command);
	printf("Arguments:\n");
	while (i < node->arg_count)
	{
		printf("[%d]: %s\n", i, node->args[i]);
		i++;
	}
}

char	*get_path_from_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] && ft_strnstr(envp[i], "PATH", 4) == NULL)
		i++;
	if (envp[i] == NULL)
		return (NULL);
	return (envp[i] + 5);
}

char	*find_command_path(char *cmd, char *path_str)
{
	char	**file_paths;
	char	*file_path;
	char	*part_path;
	int		i;

	i = 0;
	file_paths = ft_split(path_str, ':');
	while (file_paths[i])
	{
		part_path = ft_strjoin(file_paths[i], "/");
		file_path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (file_path && access(file_path, F_OK) == 0)
		{
			free_array(file_paths);
			return (file_path);
		}
		free(file_path);
		i++;
	}
	free_array(file_paths);
	return (NULL);
}

char	*find_path(char *cmd, char **envp)
{
	char	*path_str;
	char	*file_path;

	path_str = get_path_from_env(envp);
	if (path_str == NULL)
		return (NULL);
	file_path = find_command_path(cmd, path_str);
	return (file_path);
}

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

void run_child_process(char *path, char **cmd, char **envp)
{
    if (!path || execve(path, cmd, envp) == -1)
    {
        perror("execution failed");
        free_array(cmd);
        exit(1);
    }
}

void handle_parent_process(pid_t pid)
{
    waitpid(pid, NULL, 0);
}

void prepare_command_execution(char **cmd, char **envp)
{
    char *path;
    pid_t pid;

    path = find_path(cmd[0], envp);
    pid = fork();
    if (pid == -1)
        perror("fork failed");
    else if (pid == 0)
        run_child_process(path, cmd, envp);
    else
        handle_parent_process(pid);
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
