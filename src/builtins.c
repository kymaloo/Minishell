/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trgaspar <trgaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 18:34:29 by trgaspar          #+#    #+#             */
/*   Updated: 2024/10/24 18:34:30 by trgaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exit_prog(char *input)
{
	if (ft_strlen(input) == 0)
		return (0);
	if (ft_strncmp(input, "exit", ft_strlen(input)) == 0)
		return (1);
	return (0);
}
