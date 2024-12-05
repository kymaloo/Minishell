
#include "../include/minishell.h"

int run_command(char *input, char **envp)
{
	char *arg;
	int i = 0;

	while (*input)
	{
		arg = parse_argument(input);
		if (!arg)
			return (1);
		i++;
		if (ft_strcmp(arg, "env") == 0)
			display_env(envp);
		else if (ft_strcmp(arg, "export") == 0)
			builtin_export(&input, envp);
		input += ft_strlen(arg);
		while (*input && ft_isspace(*input))
			input++;
		free(arg);
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	(void)argc;
	(void)argv;
	data.env_copy = duplicate_env(envp);
	if (!data.env_copy)
	{
		perror("main: duplicate_env failed");
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		nom_tmp(&data);
		parse(&data);
		free_input(&data);
		//run_command(data.input, data.env_copy);
		//free(input);
	}
	free_all(&data);
	//free_array(data.env_copy);
	return (0);
}

void    nom_tmp(t_data *data)
{
	data->input = readline("minishell$ ");
	if (data->input && *data->input)
	{
		add_history(data->input);
	}
}
