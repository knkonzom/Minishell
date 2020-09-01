#include "minishell.h"

// Printing prompt if sigint (interrupt signal)happens
void	signal_handler(int signo)
{
	if (signo == SIGINT)
	{
		ft_putchar('\n');
        print_prompt();
	}
	return ;
}

// Handles signals in a process
void	process_sighandler(int signo)
{
	if (signo == SIGINT)
		ft_putchar('\n');
}
