
#include "../../include/minishell.h"

void remove_env(char *key, char **envp)
{
    int i = 0;

    while (envp[i])
    {
        if (ft_strncmp(envp[i], key, ft_strlen(key)) == 0 && envp[i][ft_strlen(key)] == '=')
        {
            free(envp[i]);
            while (envp[i])
            {
                envp[i] = envp[i + 1];
                i++;
            }
            return;
        }
        i++;
    }
}

int builtin_unset(char **args, char **envp)
{
    int i;

    i = 1;
    while (args[i])
    {
        if (is_valid_identifier(args[i]))
        {
            remove_env(args[i], envp);
        }
        else
        {
            ft_putstr_fd("unset: invalid identifier\n", 2);
            return (1);
        }
        i++;
    }
    return (0);
}

