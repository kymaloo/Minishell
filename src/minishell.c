/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aafounas <aafounas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 14:55:33 by aafounas          #+#    #+#             */
/*   Updated: 2024/10/22 16:10:20 by aafounas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int main(void) 
{
    char *input;

    while (1) 
    {
        input = readline("minishell$ ");

        if (input && *input) 
        {
            add_history(input);
        }

        free(input);
    }
    return 0;
}
