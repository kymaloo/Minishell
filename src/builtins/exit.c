
#include "../../include/minishell.h"

int builtin_exit(t_token *token)
{
    int exit_code = 0;
    t_token *arg_token = token->next;
    
    if (arg_token && arg_token->character)
    {
        exit_code = ft_atoi(arg_token->character);
    }
    printf("exit\n");
    exit(exit_code);
}
