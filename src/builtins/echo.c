
#include "../../include/minishell.h"

int is_n_flag(t_token *token)
{
    int i;

    if (!token || token->character[0] != '-' || token->character[1] != 'n')
        return (0);
    i = 1;
    while (token->character[++i])
        if (token->character[i] != 'n')
            return (0);
    return (1);
}

char *process_argument(t_token *token, char **envp)
{
    char *result;

    if (!token)
        return (NULL);
    if (token->character[0] == '"' || token->character[0] == '\'')
        result = quotes_env(token->character);
    else
        result = expand_variable(token->character, envp);
    return (result);
}

int builtin_echo(t_token *tokens, char **envp)
{
    int n_flag;
    int first;
    char *processed_arg;
    t_token *token = tokens;

    n_flag = 0;
    if (token && is_n_flag(token))
    {
        n_flag = 1;
        token = token->next;
    }
    first = 1;
    while (token)
    {
        processed_arg = process_argument(token, envp);
        if (!first)
            ft_putstr_fd(" ", 1);
        first = 0;
        ft_putstr_fd(processed_arg, 1);
        free(processed_arg);
        token = token->next;
    }
    if (!n_flag)
        ft_putstr_fd("\n", 1);
    return (0);
}
