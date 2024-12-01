
#include "../../include/minishell.h"

int has_unmatched_quotes(const char *str)
{
    char quote = 0;

    if (!str)
        return (1);

    while (*str)
    {
        if ((*str == '"' || *str == '\''))
        {
            if (!quote)
                quote = *str;
            else if (quote == *str)
                quote = 0;
        }
        str++;
    }
    return (quote != 0);
}

int validate_and_clean(char *arg, char **cleaned)
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
}

int handle_export_arg(const char *input, char **envp)
{
    char *parsed_arg;
    char *cleaned_arg;

    if (!input || !*input)
    {
        fprintf(stderr, "handle_export_arg: empty argument\n");
        return (1);
    }

    // Log pour vérifier l'entrée
    debug_log("handle_export_arg: received input '%s'", input);
    
    parsed_arg = parse_argument(input);
    if (!parsed_arg)
    {
        fprintf(stderr, "export: unmatched quotes\n");
        return (1);
    }
    
    // Log pour vérifier le résultat de `parse_argument`
    debug_log("handle_export_arg: parsed argument '%s'", parsed_arg);
    
    cleaned_arg = trim_quotes(parsed_arg);
    free(parsed_arg);
    
    if (!cleaned_arg)
    {
        fprintf(stderr, "export: invalid identifier '%s'\n", input);
        return (1);
    }
    
    // Log pour vérifier après le nettoyage des guillemets
    debug_log("handle_export_arg: cleaned argument '%s'", cleaned_arg);

    if (!is_valid_identifier(cleaned_arg))
    {
        fprintf(stderr, "export: '%s': not a valid identifier\n", cleaned_arg);
        free(cleaned_arg);
        return (1);
    }

    // Log avant d'ajouter ou de mettre à jour l'environnement
    debug_log("handle_export_arg: adding or updating environment with '%s'", cleaned_arg);

    add_or_update_env(cleaned_arg, envp);
    free(cleaned_arg);
    
    return (0);
}

int builtin_export(char **args, char **envp)
{
    int i = 1;

    // Log avant de commencer la gestion des arguments
    debug_log("builtin_export: processing arguments");

    if (!args || !args[1])
    {
        // Log si l'argument est vide, on affiche l'environnement
        debug_log("builtin_export: no arguments, displaying environment");
        
        // Afficher l'environnement avec 'declare -x'
        display_export_env(envp);
        return (0);
    }

    while (args[i])
    {
        // Log pour chaque argument traité
        debug_log("builtin_export: handling argument '%s'", args[i]);

        if (handle_export_arg(args[i], envp) != 0)
        {
            fprintf(stderr, "builtin_export: failed to handle '%s'\n", args[i]);
            return (1);
        }
        i++;
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




