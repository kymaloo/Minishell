
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

int execute_builtin(t_token *token, t_token *args, char **envp)
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
}
