
#include "../../include/minishell.h"

int	is_n_flag(char *str)
{
	int	i;

	if (!str || str[0] != '-' || str[1] != 'n')
		return (0);
	i = 1;
	while (str[++i])
		if (str[i] != 'n')
			return (0);
	return (1);
}

char	*process_argument(char *arg, char **envp)
{
	char	*result;

	if (!arg)
		return (NULL);

	if (*arg == '"' || *arg == '\'')
		result = remove_quotes(arg, envp);
	else
		result = expand_variable(arg, envp);
	return (result);
}
char *remove_quotes(const char *arg, char **envp)
{
    (void)arg;
    (void)envp;
    return NULL;
}

char *expand_variable(const char *arg, char **envp)
{
    (void)arg;
    (void)envp;
    return NULL;
}

int	builtin_echo(char **args, char **envp)
{
	int	n_flag;
	int	i;
	int	first;
	char	*processed_arg;

	n_flag = 0;
	i = 1;
	if (args[1] && is_n_flag(args[1]))
	{
		n_flag = 1;
		while (args[i] && is_n_flag(args[i]))
			i++;
	}
	first = 1;
	while (args[i])
	{
		processed_arg = process_argument(args[i], envp);
		if (!first)
			ft_putstr_fd(" ", 1);
		first = 0;
		ft_putstr_fd(processed_arg, 1);
		free(processed_arg);
		i++;
	}
	if (!n_flag)
		ft_putstr_fd("\n", 1);
	return (0);
}
