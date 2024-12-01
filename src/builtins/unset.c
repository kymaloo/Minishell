
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

int builtin_unset(t_token *tokens, char **envp)
{
    t_token *token = tokens;

    while (token)
    {
        if (is_valid_identifier(token->character))
        {
            remove_env(token->character, envp);
        }
        else
        {
            ft_putstr_fd("unset: invalid identifier\n", 2);
            return (1);
        }
        token = token->next;
    }
    return (0);
}

