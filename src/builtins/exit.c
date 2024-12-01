
#include "../../include/minishell.h"

int builtin_exit(char **args)
{
    int exit_code;

    exit_code = 0;
    if (args[1])
        exit_code = ft_atoi(args[1]);
    printf("exit\n");
    exit(exit_code);
}