

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../libft/libft.h"

typedef struct s_command_node {
    char *cmd;
    char **args;
    int arg_count;
} t_command_node;

typedef struct s_ast_node {
    char *cmd;
    char **args;
    struct s_ast_node *left;
    struct s_ast_node *right;
    int is_pipe;
    int is_redirection;
} t_ast_node;

/*///////////////////////EXEC////////////////////*/
void	print_command_info(t_command_node *node);
char	*get_path_from_env(char **envp);
char	*find_command_path(char *cmd, char *path_str);
char	*find_path(char *cmd, char **envp);
void	free_array(char **arr);
void	error(char *msg);
void	execute_basic(char *argv, char **envp);
void handle_output_redirection(char **cmd, int *stdout_backup, int i);
void handle_input_redirection(char **cmd, int *stdin_backup, int i);
void handle_redirection(char **cmd, int *stdin_backup, int *stdout_backup);
void restore_redirection(int stdin_backup, int stdout_backup);
void run_child_process(char *path, char **cmd, char **envp);
void handle_parent_process(pid_t pid);
void prepare_command_execution(char **cmd, char **envp);
void execute(char *argv, char **envp);
int	run_command(char *input, char **envp);
/*//////////////////////BUILTIN//////////////////*/
int builtin_cd(char **args, char **envp);
int	is_n_flag(char *str);
char *remove_quotes(const char *arg, char **envp);
char *expand_variable(const char *arg, char **envp);
int builtin_echo(char **args, char **envp);
void update_env(char *name, char *value, char **envp);
char **duplicate_env(char **envp);
int ft_isspace(char c);
void duplicate_env_copy(char **envp, char **new_env, int count);
void update_env_replace(char **envp, int index, char *new_entry);
void update_env_add(char **envp, int i, char *new_entry);
int	ft_strcmp(const char *s1, const char *s2);
int is_builtin(char *cmd);
int execute_builtin(char **args, char **envp);
int has_unmatched_quotes(const char *str);
int display_env(char **envp);
char *trim_quotes(const char *input);
int handle_export_arg(const char *input, char **envp);
int validate_and_clean(char *arg, char **cleaned);
void add_or_update_env(const char *arg, char **envp);
int builtin_export(char **args, char **envp);
int is_duplicate(char **envp, const char *arg);
char *ft_strcat(char *dest, const char *src);
char *parse_argument(const char *input);
void free_arguments(char **args);
int builtin_unset(char **args, char **envp);
int is_valid_identifier(const char *str);
int update_env_value(char **env, const char *new_entry);
int display_export_env(char **envp);
char *quotes_env(const char *str);
void debug_log(const char *format, ...);
void add_or_update_env(const char *arg, char **envp);
char *get_env_name(const char *arg);
void remove_env(char *key, char **envp);
int builtin_exit(char **args);
int builtin_pwd(void);


#endif