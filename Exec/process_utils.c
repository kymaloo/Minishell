
#include "../../include/minishell.h"

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