/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trgaspar <trgaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 18:36:26 by trgaspar          #+#    #+#             */
/*   Updated: 2024/10/24 18:37:20 by trgaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse(t_data *data)
{
	int	status;

	status = EXIT_SUCCESS;
	if (data->input == NULL)
		return (EXIT_FAILURE);
	status = parse_quote(data);
	if (status == EXIT_FAILURE)
	{
		printf("Error: Parse quote failed\n");
		return (status);
	}
	ft_lstclear(&data->lst);
	return (status);
}

int	parse_quote(t_data *data)
{
	int	status;

	status = EXIT_SUCCESS;
	status = quote_is_pair(data);
	if (status == EXIT_FAILURE)
		return (status);
	stock_char_lst(data);
	transform_char(data, T_DOUBLE_QUOTE);
	transform_char(data, T_SIMPLE_QUOTE);
	check_dollar(data, T_DOUBLE_QUOTE);
	stock_string_token(data);
	//print_lst(data);
	return (status);
}

void	free_input(t_data *data)
{
	free(data->input);
	data->input = NULL;
}

void	free_all(t_data *data)
{
	free_input(data);
	rl_clear_history();
}
