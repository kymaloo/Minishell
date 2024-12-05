#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"

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
	char			**env_copy;
	t_list			*lst;
	t_token			*token;
	t_token			*tmp;
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
void	print_lst_token(t_data *data, int identifier);

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
void	stock_str_in_lst(t_data *data, char *str);
void	transform_all_tokens_into_characters(t_data *data, int token);
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
void	stock_string_token(t_data *data, int identifier);
int		count_handle_quote(t_list *cursor, int type);
void	handle_and_store_token(t_data *data, t_list **cursor, int type, int tk, int identifier);
void	handle_symbol_token(t_data *data, t_list **cursor, int	identifier);

char	*recup_expand(t_data *data, int identifier);
char	*recup_var_env(t_data *data, int identifier);
void	replace_expand(t_data *data, int identifier);

int		check_dollar_in_double_quote(char *str);
void	expand(t_data *data);
int		count_all_character_lst(t_data *data);
char	*stock_all_character_lst(t_data *data);
void	ft_lstclear_tmp(t_token **tmp);

//EXPAND
char	*recup_expand(t_data *data, int identifier);
char	*recup_var_env(t_data *data, int identifier);
void	replace_expand(t_data *data, int identifier);
int		check_dollar_in_double_quote(char *str);

//EXPAND_UTILS
void	replace_expand_in_double_quote(t_data *data);
void	handle_double_quote(t_token *cursor, t_data *data);
char	*extract_content_between_quotes(char *str);
char	*stock_all_character_lst(t_data *data);
int		count_all_character_lst(t_data *data);

void nom_tmp(t_data *data);

#endif