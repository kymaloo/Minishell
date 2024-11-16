/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trgaspar <trgaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 14:55:33 by aafounas          #+#    #+#             */
/*   Updated: 2024/10/25 20:47:46 by trgaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	t_data	data;

	init_data(&data);
	while (1)
	{
		nom_tmp(&data);
		if (exit_prog(data.input))
			break;
		parse(&data);
		free_input(&data);
	}
	free_all(&data);
	return (0);
}

void	nom_tmp(t_data *data)
{
	data->input = readline("minishell$ ");
	if (*data->input && data->input)
	{
		add_history(data->input);
	}
}
