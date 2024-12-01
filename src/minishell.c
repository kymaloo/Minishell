
#include "../include/minishell.h"

int run_command(char *input, char **envp)
{
    char *arg;
    int i = 0;

    while (*input)
    {
        arg = parse_argument(input);
        if (!arg)
            return (1);
        i++;
        if (ft_strcmp(arg, "env") == 0)
            display_env(envp);
        else if (ft_strcmp(arg, "export") == 0)
            builtin_export(&input, envp);
        input += ft_strlen(arg);
        while (*input && ft_isspace(*input))
            input++;
        free(arg);
    }
    return (0);
}

int	main(int argc, char **argv, char **envp)
{
	char	**env_copy;
	char	*input;

	(void)argc;
	(void)argv;
	env_copy = duplicate_env(envp);
	if (!env_copy)
	{
		perror("main: duplicate_env failed");
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		input = readline("minishell$ ");
		if (input && *input)
		{
			add_history(input);
			run_command(input, env_copy);
		}
		free(input);
	}
	free_array(env_copy);
	return (0);
}
