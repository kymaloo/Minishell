#include "../include/minishell.h"

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

//Gestion des quotes

int	parse_quote(t_data *data)
{
	int	status;

	status = EXIT_SUCCESS;
	status = quote_is_pair(data);
	if (status == EXIT_FAILURE)
		return (status);
	stock_str_in_lst(data, data->input);
	//print_lst(data);
	//delete_all_consecutive(data, T_DOUBLE_QUOTE);
	//delete_all_consecutive(data, T_SIMPLE_QUOTE);
	print_lst(data);
	transform_all_tokens_into_characters(data, T_DOUBLE_QUOTE);
	transform_all_tokens_into_characters(data, T_SIMPLE_QUOTE);
	check_dollar(data, T_DOUBLE_QUOTE, 0);
	expand(data);
	ft_lstclear_token(&data->token);
	return (status);
}

//Gestion des expands
void	expand(t_data *data)
{
	stock_string_token(data, TOKEN);
	ft_lstclear(&data->lst);
	detete_dollars_before_quote(data, T_WORD_DOUBLE_QUOTE);
	replace_expand(data, TOKEN);
	replace_expand_in_double_quote(data);
	//print_lst_token(data, TOKEN);
	//printf("%d\n", count_regroup_symbole(data->token, T_BROKET_LEFT));
	//regroup_symbole(data->token, '<', T_BROKET_LEFT);
	print_lst_token(data, TOKEN);
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
