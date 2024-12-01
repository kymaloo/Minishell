
#include "../../include/minishell.h"

char *merge_quoted_args(char **args, int *index)
{
    char *merged;
    char *temp;

    if (!args || !args[*index])
        return (NULL);

    merged = ft_strdup(args[*index]);
    if (!merged)
        return (perror("merge_quoted_args: malloc failed"), NULL);

    while (args[*index] && has_unmatched_quotes(merged))
    {
        temp = ft_strjoin(merged, " ");
        free(merged);
        if (!temp)
            return (perror("merge_quoted_args: malloc failed"), NULL);
        merged = ft_strjoin(temp, args[++(*index)]);
        free(temp);
        if (!merged)
            return (perror("merge_quoted_args: malloc failed"), NULL);
    }
    return (merged);
}

int ft_isspace(char c)
{
    return (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\v' || c == '\f');
}

char *trim_quotes(const char *input)
{
    size_t len;
    char quote;
    char *result;

    (void)quote;
    if (!input || *input == '\0')
        return (NULL);

    len = strlen(input);
    if ((input[0] == '"' || input[0] == '\'') && input[len - 1] == input[0] && len >= 2)
    {
        result = malloc(len - 1);
        if (!result)
        {
            perror("trim_quotes: malloc failed");
            return (NULL);
        }
        strncpy(result, input + 1, len - 2);
        result[len - 2] = '\0';
        return (result);
    }
    return (NULL);
}


char *parse_argument(const char *input)
{
    size_t i = 0;
    size_t start = 0;
    char quote = 0;
    char *cleaned = NULL;

    if (!input)
        return (NULL);
    while (input[i] && ft_isspace(input[i]))
        i++;
    start = i;
    while (input[i])
    {
        if ((input[i] == '"' || input[i] == '\'') && quote == 0)
        {
            quote = input[i];
        }
        else if (input[i] == quote)
        {
            quote = 0;
        }
        i++;
        if (!quote && ft_isspace(input[i]))
            break;
    }
    if (quote)
    {
        ft_putstr_fd("parse_argument: unmatched quotes\n", 2);
        return (NULL);
    }
    cleaned = ft_substr(input, start, i - start);
    if (!cleaned)
    {
        perror("parse_argument: malloc failed");
        return (NULL);
    }

    return (cleaned);
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
