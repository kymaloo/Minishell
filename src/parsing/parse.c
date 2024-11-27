/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trgaspar <trgaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 07:29:33 by trgaspar          #+#    #+#             */
/*   Updated: 2024/11/27 09:11:35 by trgaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
/*
void	ft_lstadd_back(t_token **token, t_token *new)
{
	t_token	*tmp;

	if (!*token)
		*token = new;
	else
	{
		tmp = ft_lstlast(*token);
		tmp->next = new;
	}
}

t_token	*ft_lstlast(t_token *token)
{
	size_t	i;

	i = ft_lstsize(token);
	while (i-- > 1)
		token = token->next;
	return (token);
}

t_token	*ft_lstnew(char	input, int type)
{
	t_token	*memb;

	memb = malloc(sizeof(t_token));
	if (!memb)
		return (NULL);
	memb->character = input;
	memb->type = type;
	memb->next = NULL;
	return (memb);
}

int	ft_lstsize(t_token *token)
{
	int	i;

	i = 0;
	while (token)
	{
		token = token->next;
		i++;
	}
	return (i);
}
*/
void	stock_string_token(t_data *data)
{
	t_list	*cursor;
	
	cursor = data->lst;
	while(cursor)
	{
		if (cursor && cursor->next && cursor->type == T_DOUBLE_QUOTE)
		{
			cursor = cursor->next;
			while(cursor && cursor->next && cursor->type != T_DOUBLE_QUOTE)
			{
				printf("%c", cursor->character);
				cursor = cursor->next;
			}
			printf("\n");
		}
		else if (cursor && cursor->next && cursor->type == T_SIMPLE_QUOTE)
		{
			cursor = cursor->next;
			while(cursor && cursor->next && cursor->type != T_SIMPLE_QUOTE)
			{
				printf("%c", cursor->character);
				cursor = cursor->next;
			}
			printf("\n");
		}
		else if (cursor && cursor->next && cursor->type != T_CHARACTER)
		{
			printf("%c", cursor->character);
			printf("\n");
		}
		else
		{
			while (cursor && cursor->next && (cursor->type != T_WHITE_SPACE && cursor->type != T_PIPE && cursor->type != T_BROKET_RIGHT && cursor->type != T_BROKET_LEFT))
			{
				printf("%c", cursor->character);
				cursor = cursor->next;
			}
			printf("\n");
			printf("%c", cursor->character);
			printf("\n");
		}
		cursor = cursor->next;
	}
}

