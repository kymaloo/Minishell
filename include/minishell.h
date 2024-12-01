#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

typedef struct s_token
{
	char			*character;
	int				type;
	struct s_token	*next;
}	t_token;

typedef struct s_data
{
	int				quote_is_paire;
	char			*input;
	char			*str_stock_lst;
	t_list			*lst;
	t_token			*token;
}	t_data;

enum e_token
{
	T_PIPE,
	T_BROKET_LEFT,
	T_BROKET_RIGHT,
	T_SIMPLE_QUOTE,
	T_DOUBLE_QUOTE,
	T_DOLLAR,
	T_WHITE_SPACE,
	T_CHARACTER,
	T_DOUBLE_BROKET_LEFT,
	T_DOUBLE_BROKET_RIGHT,
	T_WORD_SIMPLE_QUOTE,
	T_WORD_DOUBLE_QUOTE,
	T_WORD,
	T_EXPAND,
};

//LST_TOKEN_UTILS
void	print_lst_token(t_data *data);

//LST_TOKEN
t_token	*ft_lstlast_token(t_token *token);
t_token	*ft_lstnew_token(char *input, int type);
void	ft_lstadd_back_token(t_token **token, t_token *new);
void	ft_lstclear_token(t_token **token);
int		ft_lstsize_token(t_token *token);

//LST_UTILS
void	print_lst(t_data *data);

//PARSE_DOLLAR
void	check_dollar(t_data *data, int token, int cpt);
int		check_quote_is_closed(t_data *data, int token);
bool	is_dollar_in_double_quotes(t_data *data);

//PARSE_INIT
void	free_input(t_data *data);
void	free_all(t_data *data);
int		parse(t_data *data);
int		parse_quote(t_data *data);

//PARSE_QUOTE
void	stock_char_lst(t_data *data);
void	transform_char(t_data *data, int token);
int		token_for_symbol(char input);
int		quote_is_pair(t_data *data);
int		simple_or_double(t_data *data, char type);

//STOCK_NEW_LST_UTILS
void	handle_quote(t_data *data, t_list **cursor, int type);
void	handle_dollar(t_data *data, t_list **cursor);
void	handle_character(t_data *data, t_list **cursor);
int		count_handle_dollar(t_list *cursor);
int		count_handle_character(t_list *cursor);

//STOCK_NEW_LST
void	stock_string_token(t_data *data);
int		count_handle_quote(t_list *cursor, int type);
void	handle_and_store_token(t_data *data, t_list **cursor, int type, int tk);
void	handle_symbol_token(t_data *data, t_list **cursor);

//MAIN
int		exit_prog(char *input);
void	nom_tmp(t_data *data);

#endif