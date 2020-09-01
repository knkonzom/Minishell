#include "minishell.h"

// Built-in clone of exit utility.
int		exit_builtin(int ac, char **command)
{
	int i;

	i = -1;
	if (ac > 2)
	{
		exit_error(1, NULL);
		return (1);
	}
	else if (ac == 1)
		exit(1);
	else
	{
		while (command[1] && command[1][++i])
			if (ft_isalpha(command[1][i]))
			{
				exit_error(2, command[1]);
				return (1);
			}
			else
				exit(ft_atoi(command[1]));
	}
	return (1337);
}

// Exit error handling
void	exit_error(int no, char *arg)
{
	if (no == 1)
		ft_putstr_fd("-minishell: exit: too many arguments\n", STDERR_FILENO);
	if (no == 2)
	{
		ft_putstr_fd("-minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
	}
}
