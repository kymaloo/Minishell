/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aafounas <aafounas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 17:33:09 by aafounas          #+#    #+#             */
/*   Updated: 2024/11/18 16:27:36 by aafounas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

int is_builtin(char *cmd)
{
    return (strcmp(cmd, "cd") == 0 || strcmp(cmd, "echo") == 0 ||
            strcmp(cmd, "exit") == 0 || strcmp(cmd, "pwd") == 0);
}

int	execute_builtin(char **args, char **envp)
{
//	int	i;

//	i = 0;
	/*while (args[i])
	{
		printf("args[%d]: '%s'\n", i, args[i]);
		i++;
	}*/
	if (ft_strcmp(args[0], "cd") == 0)
		return (builtin_cd(args, envp));
	else if (ft_strcmp(args[0], "echo") == 0)
		return (builtin_echo(args, envp));
	else if (ft_strcmp(args[0], "exit") == 0)
		return (builtin_exit(args));
	else if (ft_strcmp(args[0], "pwd") == 0)
		return (builtin_pwd());
	perror("Unknown builtin");
	return (1);
}
