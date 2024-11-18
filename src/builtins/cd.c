/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: r <r@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:10:38 by aafounas          #+#    #+#             */
/*   Updated: 2024/11/18 00:03:31 by r                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	builtin_cd(char **args, char **envp)
{
	char	cwd[1024];
	char	*target_dir;

	if (!args[1])
	{
		target_dir = getenv("HOME");
		if (!target_dir)
		{
			perror("cd: HOME not set");
			return (1);
		}
	}
	else
		target_dir = args[1];
	if (chdir(target_dir) == -1)
	{
		perror("cd");
		return (1);
	}
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		update_env("PWD", cwd, envp);
	else
		perror("cd: getcwd failed");
	return (0);
}
