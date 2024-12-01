#include "minishell.h"

int	main(void)
{
	t_data	data;

	while (1)
	{
		nom_tmp(&data);
		parse(&data);
		free_input(&data);
	}
	free_all(&data);
	return (0);
}

void	nom_tmp(t_data *data)
{
	data->input = readline("minishell$ ");
	if (data->input && *data->input)
	{
		add_history(data->input);
	}
}
