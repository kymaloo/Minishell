#include "../include/minishell.h"

void	ft_lstadd_back_token(t_token **token, t_token *new)
{
	t_token	*tmp;

	if (!new)
		return ;
	if (!*token)
		*token = new;
	else
	{
		tmp = ft_lstlast_token(*token);
		if (tmp)
			tmp->next = new;
	}
}

t_token	*ft_lstlast_token(t_token *token)
{
	if (!token)
		return (NULL);
	while (token->next)
		token = token->next;
	return (token);
}

t_token	*ft_lstnew_token(char *input, int type)
{
	t_token	*memb;

	memb = malloc(sizeof(t_token));
	if (!memb)
		return (NULL);
	memb->character = ft_strdup(input);
	if (!memb->character)
	{
		memb->character = NULL;
		free(memb);
		return (NULL);
	}
	memb->type = type;
	memb->next = NULL;
	return (memb);
}

int	ft_lstsize_token(t_token *token)
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

void	ft_lstclear_token(t_token **token)
{
	t_token	*tmp;
	t_token	*tmp2;

	if (!token)
		return ;
	tmp = *token;
	while (tmp)
	{
		tmp2 = tmp->next;
		free(tmp->character);
		free(tmp);
		tmp = tmp2;
	}
	*token = NULL;
}
