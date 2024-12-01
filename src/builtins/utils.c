
#include "../../include/minishell.h"

char *get_env_name(const char *arg)
{
    size_t len;
    char *name;

    if (!arg)
        return (NULL);
    len = 0;
    while (arg[len] && arg[len] != '=')
        len++;
    name = ft_substr(arg, 0, len);
    if (!name)
        perror("get_env_name: malloc failed");
    return (name);
}

int update_env_value(char **envp, const char *new_entry)
{
    size_t i = 0;
    char *name = get_env_name(new_entry);
    
    debug_log("update_env_value: received new entry '%s'", new_entry);
    if (!name)
        return (perror("update_env_value: malloc failed"), -1);
    while (envp[i])
    {
        if (!ft_strncmp(envp[i], name, ft_strlen(name)) && envp[i][ft_strlen(name)] == '=')
        {
            free(envp[i]);
            envp[i] = ft_strdup(new_entry);
            debug_log("update_env_value: updated '%s' to '%s'", envp[i], new_entry);
            free(name);
            return (envp[i] ? 0 : perror("update_env_value: strdup failed"), -1);
        }
        i++;
    }
    debug_log("update_env_value: no matching entry found, returning -1");
    free(name);
    return (-1);
}

void add_or_update_env(const char *arg, char **envp)
{
    char *name;

    if (!arg || !envp)
    {
        ft_putstr_fd("add_or_update_env: NULL arguments\n", 2);
        return;
    }
    debug_log("add_or_update_env: processing argument '%s'", arg);
    name = get_env_name(arg);
    if (!name)
    {
        ft_putstr_fd("add_or_update_env: failed to extract name\n", 2);
        return;
    }
    debug_log("add_or_update_env: extracted name '%s'", name);
    if (!is_valid_identifier(name))
    {
        ft_putstr_fd("add_or_update_env: invalid identifier\n", 2);
        free(name);
        return;
    }
    debug_log("add_or_update_env: calling update_env_value with '%s'", arg);
    if (update_env_value(envp, arg) < 0)
        ft_putstr_fd("add_or_update_env: update failed\n", 2);
    free(name);
}

char *quotes_env(const char *arg)
{
    size_t len;
    char *cleaned;

    if (!arg || !*arg)
    {
        ft_putstr_fd("quotes_env: NULL or empty argument\n", 2);
        return (NULL);
    }
    len = ft_strlen(arg);
    if ((arg[0] == '"' || arg[0] == '\'') && arg[len - 1] == arg[0] && len >= 2)
    {
        debug_log("quotes_env: removing surrounding quotes from '%s'", arg);
        cleaned = ft_substr(arg, 1, len - 2);
    }
    else
        cleaned = ft_strdup(arg);
    if (!cleaned)
        return (perror("quotes_env: malloc failed"), NULL);
    return (cleaned);
}
