/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aafounas <aafounas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 14:49:57 by aafounas          #+#    #+#             */
/*   Updated: 2024/11/14 14:18:35 by aafounas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int main(int argc, char *argv[])
{
    char cwd[1024];

    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s <path>\n", argv[0]);
        return 1;
    }

    if (getcwd(cwd, sizeof(cwd)) != NULL)
        printf("Current directory: %s\n", cwd);

    printf("Attempting to change to: %s\n", argv[1]);

    if (access(argv[1], F_OK) == -1)
    {
        perror("Directory does not exist");
        return 1;
    }

    if (chdir(argv[1]) == -1)
    {
        perror("chdir failed");
        return 1;
    }

    if (getcwd(cwd, sizeof(cwd)) != NULL)
        printf("Directory successfully changed to: %s\n", cwd);
    else
        perror("getcwd failed after chdir");

    return 0;
}*/
#include <stdio.h>
#include <unistd.h>

int main()
{
    char *path = "/home/aafounas/Documents/minishell/src";

    printf("Attempting to change to: %s\n", path);
    if (chdir(path) == -1)
    {
        perror("chdir failed");
        return 1;
    }

    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        printf("Directory changed to: %s\n", cwd);
    }
    else
    {
        perror("getcwd failed");
    }

    return 0;
}
