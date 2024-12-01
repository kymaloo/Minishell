

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
# include <stdbool.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../libft/libft.h"

typedef struct s_command_node {
    char *cmd;
    char **args;
    int arg_count;
} t_command_node;

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

/*///////////////////////EXEC////////////////////*/
void	print_command_info(t_token *tokens);
char	*get_path_from_env(char **envp);
char	*find_command_path(char *cmd, char *path_str);
char	*find_path(char *cmd, char **envp);
void	free_array(char **arr);
void	error(char *msg);
void	execute_basic(t_token *tokens, char **envp);
void handle_output_redirection(t_token **tokens, int *stdout_backup, t_token *current);
void handle_input_redirection(t_token **tokens, int *stdin_backup, t_token *current);
void handle_redirection(t_token **tokens, int *stdin_backup, int *stdout_backup);
void restore_redirection(int stdin_backup, int stdout_backup);
void run_child_process(char *path, t_token *tokens, char **envp);
void handle_parent_process(pid_t pid);
void	handle_redirection_tokens(t_token *tokens, int *stdin_backup, int *stdout_backup);
void prepare_command_execution(t_token *tokens, char **envp);
void	execute(t_token *tokens, char **envp);
int run_command(char *input, char **envp);
void	handle_redirection_tokens(t_token *tokens, int *stdin_backup, int *stdout_backup);
/*//////////////////////BUILTIN//////////////////*/
int builtin_cd(t_token *tokens, char **envp);
int is_n_flag(t_token *token);
char *process_argument(t_token *token, char **envp);
char *remove_quotes(const char *arg, char **envp);
char *expand_variable(const char *arg, char **envp);
int builtin_echo(t_token *tokens, char **envp);
void update_env(char *name, char *value, t_token **env_list);
void free_env_list(t_token **env_list);
t_token *duplicate_env(char **envp);
int ft_isspace(char c);
char **convert_tokens_to_args(t_token *args);
char **convert_env_to_array(t_token *env_list);
void free_env_list(t_token **env_list);
//void update_env_replace(char **envp, int index, char *new_entry);
//void update_env_add(char **envp, int i, char *new_entry);
int	ft_strcmp(const char *s1, const char *s2);
int is_builtin(t_token *token);
int execute_builtin(t_token *token, t_token *args, char **envp);
char *merge_quoted_args(t_token *tokens);
int display_env(char **envp);
char *trim_quotes(const char *input);
int handle_export_arg(t_token *token, char **envp);
//int validate_and_clean(char *arg, char **cleaned);
char **convert_env_to_array(t_token *env_list);
int builtin_export(t_token *tokens, char **envp);
int is_duplicate(char **envp, const char *arg);
char *ft_strcat(char *dest, const char *src);
char *parse_argument(const char *input);
void free_arguments(char **args);
int builtin_unset(t_token *tokens, char **envp);
int is_valid_identifier(const char *str);
int update_env_value(char **envp, const char *new_entry);
int display_export_env(char **envp);
char *quotes_env(const char *arg);
void debug_log(const char *format, ...);
void add_or_update_env(const char *arg, char **envp);
char *get_env_name(const char *arg);
void remove_env(char *key, char **envp);
int builtin_exit(t_token *token);
int builtin_pwd(void);
int main(int argc, char **argv, char **envp);


#endif