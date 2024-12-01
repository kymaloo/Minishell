
#include "../../include/minishell.h"

void run_child_process(char *path, t_token *tokens, char **envp)
{
    char **cmd;

    cmd = tokens_to_array(tokens);
    if (!path || execve(path, cmd, envp) == -1)
    {
        perror("execution failed");
        ft_free_array(cmd);
        exit(1);
    }
    ft_free_array(cmd);
}

void handle_parent_process(pid_t pid)
{
    if (waitpid(pid, NULL, 0) == -1)
        perror("waitpid failed");
}

void prepare_command_execution(t_token *tokens, char **envp)
{
    char *path;
    pid_t pid;

    path = find_path(tokens->character, envp);
    pid = fork();
    if (pid == -1)
        perror("fork failed");
    else if (pid == 0)
        run_child_process(path, tokens, envp);
    else
        handle_parent_process(pid);
    if (path)
        free(path);
}