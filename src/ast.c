/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aafounas <aafounas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 16:23:34 by aafounas          #+#    #+#             */
/*   Updated: 2024/11/06 18:11:27 by aafounas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_ast_node  *create_ast_node(char *cmd, char **args)
{
    t_ast_node  *node;

    node = malloc(sizeof(t_ast_node));
    if (!node)
        return (NULL);
    node->cmd = cmd;
    node->args = args;
    node->left = NULL;
    node->right = NULL;
    node->is_pipe = 0;
    node->is_redirection = 0;
    return (node);
}

void execute_command(t_ast_node *node, char **envp)
{
    if (execve(node->cmd, node->args, envp) == -1)
    {
        perror("execution failed");
        exit(1);
    }
}

void execute_ast(t_ast_node *node, char **envp)
{
    if (!node)
        return ;

    if (is_builtin(node->cmd))
    {
        execute_builtin(node->args, envp);
        return ; 
    }
    if (node->is_pipe)
    {
        int pipe_fd[2];
        if (pipe(pipe_fd) == -1)
        {
            perror("pipe failed");
            return;
        }
        pid_t pid = fork();
        if (pid == -1)
            perror("fork failed");
        else if (pid == 0)
        {
            close(pipe_fd[0]);
            dup2(pipe_fd[1], STDOUT_FILENO);
            execute_ast(node->left, envp);
            close(pipe_fd[1]);
            exit(0);
        }
        else
        {
            close(pipe_fd[1]);
            dup2(pipe_fd[0], STDIN_FILENO);
            execute_ast(node->right, envp);
            close(pipe_fd[0]);
            waitpid(pid, NULL, 0);
        }
    }
    else if (node->is_redirection)
    {
        handle_redirection(node->args, NULL, NULL);
        execute_command(node, envp);
    }
    else
    {
        execute_command(node, envp);
    }
}
