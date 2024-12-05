
#include "../../include/minishell.h"

int is_valid_identifier(const char *str)
{
    if (!str || !(ft_isalpha(*str) || *str == '_'))
        return (0);
    while (*str && *str != '=')
    {
        if (!(ft_isalnum(*str) || *str == '_'))
            return (0);
        str++;
    }
    return (1);
}

int is_duplicate(char **envp, const char *arg)
{
    size_t i;
    size_t arg_len;

    if (!arg || !envp)
        return (0);
    arg_len = ft_strlen(arg);
    i = 0;
    while (envp[i])
    {
        if (!ft_strncmp(envp[i], arg, arg_len) && envp[i][arg_len] == '=')
            return (1);
        i++;
    }
    return (0);
}

int display_env(char **envp)
{
    size_t i = 0;

    if (!envp)
        return (-1);
    debug_log("display_env: displaying environment variables");
    while (envp[i])
    {
        ft_putendl_fd(envp[i], 1);
        i++;
    }
    return (0);
}


char *ft_strcat(char *dest, const char *src)
{
    size_t dest_len;
    size_t src_len;
    char *new_str;

    if (!dest || !src)
        return (NULL);
    dest_len = ft_strlen(dest);
    src_len = ft_strlen(src);
    new_str = malloc(dest_len + src_len + 1);
    if (!new_str)
    {
        perror("ft_strcat: malloc failed");
        return (NULL);
    }
    ft_memcpy(new_str, dest, dest_len);
    ft_memcpy(new_str + dest_len, src, src_len + 1);
    free(dest);
    return (new_str);
}

void debug_log(const char *format, ...)
{
    va_list args;

    va_start(args, format);
    ft_putstr_fd("DEBUG: ", 2);
    vdprintf(2, format, args);
    ft_putchar_fd('\n', 2);
    va_end(args);
}
