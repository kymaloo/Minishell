
#include "../../include/minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

int is_builtin(t_token *token)
{
    if (!token || !token->character)
        return (0);
    return (ft_strcmp(token->character, "cd") == 0 || 
            ft_strcmp(token->character, "echo") == 0 ||
            ft_strcmp(token->character, "exit") == 0 || 
            ft_strcmp(token->character, "pwd") == 0 ||
            ft_strcmp(token->character, "export") == 0 || 
            ft_strcmp(token->character, "unset") == 0);
}
char **convert_tokens_to_args(t_token *args)
{
    t_token *tmp = args;
    int i = 0;
    int args_count = 0;

    while (tmp)
    {
        args_count++;
        tmp = tmp->next;
    }
    char **args_array = malloc(sizeof(char *) * (args_count + 1));
    if (!args_array)
    {
        perror("Memory allocation failed");
        return (NULL);
    }
    tmp = args;
    while (tmp)
    {
        args_array[i] = tmp->character;
        i++;
        tmp = tmp->next;
    }
    args_array[i] = NULL;
    return (args_array);
}

/*int execute_builtin(t_token *token, t_token *args, char **envp)
{
    if (ft_strcmp(token->character, "cd") == 0)
        return (builtin_cd(args, envp));
    else if (ft_strcmp(token->character, "echo") == 0)
        return (builtin_echo(args, envp));
    else if (ft_strcmp(token->character, "exit") == 0)
        return (builtin_exit(args));
    else if (ft_strcmp(token->character, "pwd") == 0)
        return (builtin_pwd());
    else if (ft_strcmp(token->character, "export") == 0)
        return (builtin_export(args, envp));
    else if (ft_strcmp(token->character, "unset") == 0)
        return (builtin_unset(args, envp));
    
    perror("Unknown builtin");
    return (1);
}*/
int execute_builtin(t_token *token, t_token *args, char **envp)
{
    char **args_array = convert_tokens_to_args(args);
    
    if (!args_array)
    {
        return (1);
    }
    int result = 1;
    if (ft_strcmp(token->character, "cd") == 0)
        result = builtin_cd(args_array, envp);
    else if (ft_strcmp(token->character, "echo") == 0)
        result = builtin_echo(args_array, envp);
    else if (ft_strcmp(token->character, "exit") == 0)
        result = builtin_exit(args_array);
    else if (ft_strcmp(token->character, "pwd") == 0)
        result = builtin_pwd();
    else if (ft_strcmp(token->character, "export") == 0)
        result = builtin_export(args_array, envp);
    else if (ft_strcmp(token->character, "unset") == 0)
        result = builtin_unset(args_array, envp);
    else
    {
        perror("Unknown builtin");
        result = 1;
    }
    free(args_array);
    return (result);
}
