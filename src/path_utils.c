/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aafounas <aafounas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 17:08:33 by aafounas          #+#    #+#             */
/*   Updated: 2024/11/02 17:13:17 by aafounas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_path_from_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] && ft_strnstr(envp[i], "PATH", 4) == NULL)
		i++;
	if (envp[i] == NULL)
		return (NULL);
	return (envp[i] + 5);
}

char	*find_command_path(char *cmd, char *path_str)
{
	char	**file_paths;
	char	*file_path;
	char	*part_path;
	int		i;

	i = 0;
	file_paths = ft_split(path_str, ':');
	while (file_paths[i])
	{
		part_path = ft_strjoin(file_paths[i], "/");
		file_path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (file_path && access(file_path, F_OK) == 0)
		{
			free_array(file_paths);
			return (file_path);
		}
		free(file_path);
		i++;
	}
	free_array(file_paths);
	return (NULL);
}

char	*find_path(char *cmd, char **envp)
{
	char	*path_str;
	char	*file_path;

	path_str = get_path_from_env(envp);
	if (path_str == NULL)
		return (NULL);
	file_path = find_command_path(cmd, path_str);
	return (file_path);
}