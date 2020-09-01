#include "minishell.h"

// Print unknown command error
int	print_error(char *command)
{
	ft_putstr_fd("-minishell: ", STDERR_FILENO);
	ft_putstr_fd(command, STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
	return (-1);
}

// Print env errors
int		env_error(char *arg)
{
	ft_putstr_fd("env: ", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
	return (1);
}