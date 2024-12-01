#include "minishell.h"

int run_command(char *input, char **envp)
{
    t_data data;
    t_token *tokens;
    int i = 0;

    data.input = input;
    tokens = NULL;
    parse(&data);
    while (data.token)
    {
        if (is_builtin(data.token->character))
        {
            if (execute_builtin(&data.token, envp) != 0)
            {
                fprintf(stderr, "Error: Failed to execute builtin '%s'\n", data.token->character);
                return (1);
            }
		}
        data.token = data.token->next;
    }
    free_input(&data);
    return (0);
}


int main(int argc, char **argv, char **envp)
{
    char *input;
    char **env_copy;

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

