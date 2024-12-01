
#include "../../include/minishell.h"

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

void	execute_basic(t_token *tokens, char **envp)
{
	char	**cmd;
	char	*path;

	cmd = tokens_to_array(tokens);
	if (!cmd)
		error("token to array conversion failed");
	path = find_path(cmd[0], envp);
	if (!path || execve(path, cmd, envp) == -1)
	{
		free_array(cmd);
		error("execution failed");
	}
	free_array(cmd);
}

void	handle_redirection_tokens(t_token *tokens, int *stdin_backup, int *stdout_backup)
{
	t_token	*cursor;
	int		fd;

	cursor = tokens;
	while (cursor)
	{
		if (cursor->type == T_BROKET_RIGHT && cursor->next)
		{
			fd = open(cursor->next->character, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd == -1)
				perror("open");
			else
			{
				*stdout_backup = dup(1);
				dup2(fd, 1);
				close(fd);
			}
		}
		else if (cursor->type == T_BROKET_LEFT && cursor->next)
		{
			fd = open(cursor->next->character, O_RDONLY);
			if (fd == -1)
				perror("open");
			else
			{
				*stdin_backup = dup(0);
				dup2(fd, 0);
				close(fd);
			}
		}
		cursor = cursor->next;
	}
}

void	execute(t_token *tokens, char **envp)
{
	int	stdin_backup;
	int	stdout_backup;

	stdin_backup = -1;
	stdout_backup = -1;
	handle_redirection_tokens(tokens, &stdin_backup, &stdout_backup);
	prepare_command_execution(tokens, envp);
	restore_redirection(stdin_backup, stdout_backup);
}
