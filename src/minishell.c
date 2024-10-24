/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trgaspar <trgaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 14:55:33 by aafounas          #+#    #+#             */
/*   Updated: 2024/10/24 18:48:43 by trgaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	//t_ptoken	*ptoken;
	char		*input;

	while (1)
	{
		input = readline("minishell$ ");
		if (exit_prog(input) == 1)
			break ;
		if (input && *input)
		{
			add_history(input);
		}
		rl_on_new_line();
		free(input);
	}
	return (0);
}
