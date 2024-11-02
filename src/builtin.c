/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aafounas <aafounas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 17:33:09 by aafounas          #+#    #+#             */
/*   Updated: 2024/11/02 17:44:26 by aafounas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int builtin_echo(char **args)
{
    int i;

    i = 1;
    while (args[i])
    {
        printf("%s", args[i]);
        if (args[i + 1])
            printf(" ");
        i++;
    }
    printf("\n");
    return 0;
}
