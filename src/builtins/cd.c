/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aafounas <aafounas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:10:38 by aafounas          #+#    #+#             */
/*   Updated: 2024/11/07 16:34:38 by aafounas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
/*
int builtin_cd(char **args, char **envp)
{
    char cwd[1024];

    if (getcwd(cwd, sizeof(cwd)) != NULL)
        update_env("OLDPWD", cwd, envp);
    if (!args[1])
    {
        fprintf(stderr, "cd: missing argument\n");
        return 1;
    }
    printf("Current directory: %s\n", cwd);
    printf("Attempting to change to: %s\n", args[1]);
    if (access(args[1], F_OK) == -1)
    {
        perror("cd failed - directory does not exist");
        return 1;
    }
    printf("Path argument: %s\n", args[1]);
    if (chdir(args[1]) == -1)
    {
        perror("cd failed");
        return 1;
    }
    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        printf("Directory changed to: %s\n", cwd);
        update_env("PWD", cwd, envp);
    }
    else
        perror("getcwd failed after cd");
    return 0;
}*/

int builtin_cd(char **args, char **envp)
{
    (void)envp;
    char cwd[1024];
    int i;

    if (!args[1])
    {
        fprintf(stderr, "cd: missing argument\n");
        return 1;
    }
    printf("Path argument (character by character): ");
    for (i = 0; args[1][i] != '\0'; i++)
        printf("%d ", args[1][i]);
    printf("\n");
    printf("Attempting to change to: %s\n", args[1]);
    printf("Path length: %zu\n", strlen(args[1]));
    if (chdir(args[1]) == -1)
    {
        perror("cd failed");
        return 1;
    }
    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        printf("Directory changed to: %s\n", cwd);
    }
    else
        perror("getcwd failed after cd");
    return 0;
}

