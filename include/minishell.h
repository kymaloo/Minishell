/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aafounas <aafounas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 17:15:31 by aafounas          #+#    #+#             */
/*   Updated: 2024/10/29 17:53:38 by aafounas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../libft/libft.h"

typedef struct s_command_node {
    char *cmd;
    char **args;
    int arg_count;
} t_command_node;

typedef struct s_ast_node {
    char *cmd;
    char **args;
    struct s_ast_node *left;
    struct s_ast_node *right;
    int is_pipe;
    int is_redirection;
} t_ast_node;

void	print_command_info(t_command_node *node);
char	*get_path_from_env(char **envp);
char	*find_command_path(char *cmd, char *path_str);
char	*find_path(char *cmd, char **envp);
void	free_array(char **arr);
void	error(char *msg);
void	execute_basic(char *argv, char **envp);
void handle_output_redirection(char **cmd, int *stdout_backup, int i);
void handle_input_redirection(char **cmd, int *stdin_backup, int i);
void handle_redirection(char **cmd, int *stdin_backup, int *stdout_backup);
void restore_redirection(int stdin_backup, int stdout_backup);
void run_child_process(char *path, char **cmd, char **envp);
void handle_parent_process(pid_t pid);
void prepare_command_execution(char **cmd, char **envp);
void execute(char *argv, char **envp);


#endif