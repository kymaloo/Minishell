
#include "../../include/minishell.h"

t_token *duplicate_env(char **envp)
{
	t_token *env_list = NULL;
	t_token *new_node;
	int i = 0;

	while (envp[i])
	{
		new_node = ft_lstnew_token(envp[i], T_ENV);
		if (!new_node)
		{
			perror("duplicate_env: malloc failed");
			ft_lstclear_token(&env_list);
			exit(EXIT_FAILURE);
		}
		ft_lstadd_back_token(&env_list, new_node);
		i++;
	}
	return (env_list);
}

char **convert_env_to_array(t_token *env_list)
{
	char **env_array;
	int i = 0;
	t_token *cursor = env_list;

	env_array = malloc((ft_lstsize_token(env_list) + 1) * sizeof(char *));
	if (!env_array)
	{
		perror("convert_env_to_array: malloc failed");
		return (NULL);
	}
	while (cursor)
	{
		env_array[i] = ft_strdup(cursor->character);
		if (!env_array[i])
		{
			perror("convert_env_to_array: malloc failed");
			free_array(env_array);
			return (NULL);
		}
		cursor = cursor->next;
		i++;
	}
	env_array[i] = NULL;
	return (env_array);
}

void update_env(char *name, char *value, t_token **env_list)
{
	t_token *cursor = *env_list;
	char *new_entry;
	int name_len = ft_strlen(name);

	new_entry = malloc(name_len + ft_strlen(value) + 2);
	if (!new_entry)
	{
		perror("update_env: malloc failed");
		return;
	}
	ft_strlcpy(new_entry, name, name_len + 1);
	ft_strlcat(new_entry, "=", name_len + 2);
	ft_strlcat(new_entry, value, name_len + ft_strlen(value) + 2);
	while (cursor)
	{
		if (ft_strncmp(cursor->character, name, name_len) == 0 && cursor->character[name_len] == '=')
		{
			free(cursor->character);
			cursor->character = new_entry;
			return;
		}
		cursor = cursor->next;
	}
	t_token *new_node = ft_lstnew_token(new_entry, T_ENV);
	if (!new_node)
	{
		free(new_entry);
		perror("update_env: malloc failed");
		return;
	}
	ft_lstadd_back_token(env_list, new_node);
}

void free_env_list(t_token **env_list)
{
	ft_lstclear_token(env_list);
}
