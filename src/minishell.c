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
	t_pretoken	*pretoken;
	t_list		*lst;
	char		*input;

	pretoken = NULL;
	lst = NULL;
	while (1)
	{
		input = readline("minishell$ ");
		if (exit_prog(input) == 1)
		{
			free(input);
			break ;
		}
		stock_char_lst(&lst, pretoken, input);
		print_lst(lst);
		if (*input && input)
		{
			add_history(input);
		}
		delete_lst(lst);
		rl_on_new_line();
		free(input);
	}
	return (0);
}
