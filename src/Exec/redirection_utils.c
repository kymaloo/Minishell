
#include "../../include/minishell.h"

void handle_output_redirection(t_token **tokens, int *stdout_backup, t_token *current)
{
    int fd;

    if (!current->next || current->next->type != T_WORD)
    {
        fprintf(stderr, "minishell: syntax error near unexpected token 'newline'\n");
        return;
    }
    fd = open(current->next->character, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
    {
        perror("open");
        return;
    }
    *stdout_backup = dup(1);
    dup2(fd, 1);
    close(fd);
    ft_lstclear_token(&current->next);
    ft_lstclear_token(tokens);
}

void handle_input_redirection(t_token **tokens, int *stdin_backup, t_token *current)
{
    int fd;

    if (!current->next || current->next->type != T_WORD)
    {
        fprintf(stderr, "minishell: syntax error near unexpected token 'newline'\n");
        return;
    }
    fd = open(current->next->character, O_RDONLY);
    if (fd == -1)
    {
        perror("open");
        return;
    }
    *stdin_backup = dup(0);
    dup2(fd, 0);
    close(fd);
    ft_lstclear_token(&current->next);
    ft_lstclear_token(tokens);
}

void handle_redirection(t_token **tokens, int *stdin_backup, int *stdout_backup)
{
    t_token *current = *tokens;

    while (current)
    {
        if (current->type == T_BROKET_RIGHT) // >
        {
            handle_output_redirection(tokens, stdout_backup, current);
        }
        else if (current->type == T_BROKET_LEFT) // <
        {
            handle_input_redirection(tokens, stdin_backup, current);
        }
        current = current->next;
    }
}

void restore_redirection(int stdin_backup, int stdout_backup)
{
    if (stdin_backup != -1)
    {
        dup2(stdin_backup, 0);
        close(stdin_backup);
    }
    if (stdout_backup != -1)
    {
        dup2(stdout_backup, 1);
        close(stdout_backup);
    }
}