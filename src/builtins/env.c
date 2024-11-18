/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aafounas <aafounas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 14:14:32 by aafounas          #+#    #+#             */
/*   Updated: 2024/11/18 14:14:39 by aafounas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**duplicate_env(char **envp)
{
	int		count;
	char	**new_env;

	count = 0;
	while (envp[count])
		count++;
	new_env = malloc((count + 1) * sizeof(char *));
	if (!new_env)
	{
		perror("duplicate_env: Allocation failed");
		exit(EXIT_FAILURE);
	}
	duplicate_env_copy(envp, new_env, count);
	return (new_env);
}

void	duplicate_env_copy(char **envp, char **new_env, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		new_env[i] = ft_strdup(envp[i]);
		if (!new_env[i])
		{
			perror("duplicate_env: Allocation failed");
			exit(EXIT_FAILURE);
		}
		i++;
	}
	new_env[count] = NULL;
}

void	update_env(char *name, char *value, char **envp)
{
	int		i;
	int		name_len;
	char	*new_entry;

	name_len = ft_strlen(name);
	new_entry = malloc(name_len + ft_strlen(value) + 2);
	if (!new_entry)
	{
		perror("update_env: malloc failed");
		return ;
	}
	ft_strlcpy(new_entry, name, name_len + 1);
	ft_strlcat(new_entry, "=", name_len + 2);
	ft_strlcat(new_entry, value, name_len + ft_strlen(value) + 2);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], name, name_len) == 0 && envp[i][name_len] == '=')
		{
			update_env_replace(envp, i, new_entry);
			return ;
		}
		i++;
	}
	update_env_add(envp, i, new_entry);
}

void	update_env_replace(char **envp, int index, char *new_entry)
{
	if (envp[index])
	{
		free(envp[index]);
	}
	envp[index] = new_entry;
}

void	update_env_add(char **envp, int i, char *new_entry)
{
	envp[i] = new_entry;
	envp[i + 1] = NULL;
}
