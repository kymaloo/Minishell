/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aafounas <aafounas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:15:55 by aafounas          #+#    #+#             */
/*   Updated: 2024/11/04 16:16:19 by aafounas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int builtin_exit(char **args)
{
    int exit_code;

    exit_code = 0;
    if (args[1])
        exit_code = ft_atoi(args[1]);
    printf("exit\n");
    exit(exit_code);
}