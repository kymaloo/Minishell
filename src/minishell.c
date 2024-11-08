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
		data.input = readline("minishell$ ");
		if (*data.input && data.input)
		{
			add_history(data.input);
		}
		parse(&data);
	}
	return (0);
}

void	init_data(t_data *data)
{
	ft_bzero(data, sizeof(t_data));
}

void	parse(t_data *data)
{
	if (data->input == NULL)
		return ;
	init_tokens(data);
	parse_quotes(data);
}
