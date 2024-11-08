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

void	init_data(t_data *data)
{
	ft_bzero(data, sizeof(t_data));
}

void	parse(t_data *data)
{
    int result;

    result = 0;
	if (data->input == NULL)
		return ;
	stock_char_lst(data);
    print_lst(data);
    transform_char(data, T_SIMPLE_QUOTE);
    transform_char(data, T_DOUBLE_QUOTE);
    print_lst(data);
    delete_lst(data->lst);
    data->lst = NULL;
}
