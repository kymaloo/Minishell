/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aafounas <aafounas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 17:33:09 by aafounas          #+#    #+#             */
/*   Updated: 2024/11/06 18:11:18 by aafounas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void update_env(char *name, char *value, char **envp)
{
    int i;
    int name_len;
    char *new_entry;

    i = 0;
    name_len = ft_strlen(name);
    new_entry = malloc(name_len + strlen(value) + 2);
    if (!new_entry)
        return;
    sprintf(new_entry, "%s=%s", name, value);
    
    while (envp[i])
    {
        if (strncmp(envp[i], name, name_len) == 0 && envp[i][name_len] == '=')
        {
            free(envp[i]);
            envp[i] = new_entry;
            return;
        }
        i++;
    }

    envp[i] = new_entry;
    envp[i + 1] = NULL;
}

int is_builtin(char *cmd)
{
    return (strcmp(cmd, "cd") == 0 || strcmp(cmd, "echo") == 0 ||
            strcmp(cmd, "exit") == 0 || strcmp(cmd, "pwd") == 0);
}

int execute_builtin(char **args, char **envp)
{
    if (strcmp(args[0], "cd") == 0)
        return builtin_cd(args, envp);
    else if (strcmp(args[0], "echo") == 0)
        return builtin_echo(args);
    else if (strcmp(args[0], "exit") == 0)
        return builtin_exit(args);
    else if (strcmp(args[0], "pwd") == 0)
        return builtin_pwd();
    return 0;
}
