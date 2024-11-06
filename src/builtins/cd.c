/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aafounas <aafounas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:10:38 by aafounas          #+#    #+#             */
/*   Updated: 2024/11/06 17:51:56 by aafounas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
    if (chdir(args[1]) == -1)
    {
        perror("cd failed");
        return 1;
    }

    if (getcwd(cwd, sizeof(cwd)) != NULL)
        update_env("PWD", cwd, envp);
    return 0;
}
