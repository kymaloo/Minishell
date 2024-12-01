
#include "../../include/minishell.h"

/*int validate_and_clean(char *arg, char **cleaned)
{
    debug_log("validate_and_clean: received argument '%s'", arg);
    if (has_unmatched_quotes(arg))
    {
        debug_log("validate_and_clean: unmatched quotes in '%s'", arg);
        ft_putstr_fd("export: unmatched quotes\n", 2);
        return (1);
    }
    *cleaned = quotes_env(arg);
    if (!*cleaned)
    {
        debug_log("validate_and_clean: malloc failed for '%s'", arg);
        ft_putstr_fd("export: malloc failed\n", 2);
        return (1);
    }
    if (!is_valid_identifier(*cleaned))
    {
        debug_log("validate_and_clean: invalid identifier '%s'", *cleaned);
        ft_putstr_fd("export: invalid identifier\n", 2);
        free(*cleaned);
        *cleaned = NULL;
        return (1);
    }
    return (0);
}*/

int handle_export_arg(t_token *token, char **envp)
{
    char *cleaned_arg;

    if (!token || !token->character)
    {
        ft_putstr_fd("export: empty argument\n", 2);
        return (1);
    }
    debug_log("handle_export_arg: received input '%s'", token->character);
    cleaned_arg = quotes_env(token->character); // Utilisation de la fonction pour enlever les quotes si elles existent
    if (!cleaned_arg)
    {
        ft_putstr_fd("export: malloc failed\n", 2);
        return (1);
    }
    debug_log("handle_export_arg: cleaned argument '%s'", cleaned_arg);
    if (!is_valid_identifier(cleaned_arg))
    {
        ft_putstr_fd("export: invalid identifier\n", 2);
        free(cleaned_arg);
        return (1);
    }
    debug_log("handle_export_arg: adding or updating environment with '%s'", cleaned_arg);
    add_or_update_env(cleaned_arg, envp);
    free(cleaned_arg); 
    return (0);
}

int builtin_export(t_token *tokens, char **envp)
{
    t_token *token = tokens;
    if (!token)
    {
        display_export_env(envp);
        return (0);
    }
    while (token)
    {
        debug_log("builtin_export: handling argument '%s'", token->character);
        if (handle_export_arg(token, envp) != 0)
        {
            fprintf(stderr, "builtin_export: failed to handle '%s'\n", token->character);
            return (1);
        }
        token = token->next;
    }
    return (0);
}

int display_export_env(char **envp)
{
    size_t i = 0;

    if (!envp)
        return (-1);
    debug_log("display_export_env: displaying environment with declare -x");
    while (envp[i])
    {
        ft_putstr_fd("declare -x ", 1);
        ft_putendl_fd(envp[i], 1);
        i++;
    }
    return (0);
}
