
#include "../../include/minishell.h"

int builtin_cd(t_token *tokens, char **envp)
{
    char cwd[1024];
    char *target_dir;

    t_token *current = tokens->next;
    while (current && current->type == T_WHITE_SPACE)
        current = current->next;
    if (!current || current->type != T_CHARACTER)
    {
        target_dir = getenv("HOME");
        if (!target_dir)
        {
            perror("cd: HOME not set");
            return (1);
        }
    }
    else
        target_dir = current->character;
    if (chdir(target_dir) == -1)
    {
        perror("cd");
        return (1);
    }
    if (getcwd(cwd, sizeof(cwd)) != NULL)
        update_env("PWD", cwd, envp);
    else
        perror("cd: getcwd failed");
    return (0);
}
