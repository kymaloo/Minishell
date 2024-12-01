
#include "../../include/minishell.h"

char *merge_quoted_args(t_token *tokens)
{
    t_token *cursor = tokens;
    char *merged;
    char *temp;

    if (!cursor)
        return (NULL);
    merged = ft_strdup(cursor->character);
    if (!merged)
        return (perror("merge_quoted_args: malloc failed"), NULL);
    cursor = cursor->next;
    while (cursor)
    {
        temp = ft_strjoin(merged, " ");
        free(merged);
        if (!temp)
            return (perror("merge_quoted_args: malloc failed"), NULL);
        merged = ft_strjoin(temp, cursor->character);
        free(temp);
        if (!merged)
            return (perror("merge_quoted_args: malloc failed"), NULL);
        cursor = cursor->next;
    }
    return (merged);
}

int ft_isspace(char c)
{
    return (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\v' || c == '\f');
}


void free_arguments(char **args)
{
    size_t i;

    if (!args)
        return;
    i = 0;
    while (args[i])
    {
        free(args[i]);
        i++;
    }
    free(args);
}
