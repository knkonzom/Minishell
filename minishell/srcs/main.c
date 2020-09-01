#include "minishell.h"

// Loop that handles user input
int         main(int ac, char **av, char **env)
{
	init_env(env);
	while (1)
		minishell();
	(void)ac;
	(void)av;
	return (0);
}

// Minishell Driver
void        minishell(void)
{
	char	**command;
	char	*line;

	print_prompt();
	line = NULL;
	// Minishell starts by running prompt first, then setting line to null.
	signal(SIGINT, signal_handler);
	// Check file descriptor and line using gnl. If not blank or no error, continue to parse command.
	if (get_next_line(STDIN_FILENO, &line) != -1 && !ft_strequ(line, ""))
	{
		command = parse_command(line);
		if (ft_strlen_tab(command) == 0 || is_builtin(ft_strlen_tab(command), command) != -1)
		{
			ft_strdel(&line);
			free_command(command);
			return ;
		}
		else
			exec_command(command, g_envp);
		free_command(command);
	}
	ft_strdel(&line);
}

// Simply prints the prompt
void	print_prompt(void)
{
    ft_putstr("$>");
}

// Calls the built-in functions if the command is a built-in
int		is_builtin(int ac, char **av)
{
	if (ft_strequ(av[0], "echo"))
		return (echo_builtin(ac, av));
	if (ft_strequ(av[0], "cd"))
		return (cd_builtin(ac, av));
	if (ft_strequ(av[0], "setenv"))
		return (setenv_builtin(ac, av));
	if (ft_strequ(av[0], "unsetenv"))
		return (unsetenv_builtin(ac, av));
	if (ft_strequ(av[0], "env"))
		return (env_builtin(ac, av));
	if (ft_strequ(av[0], "exit"))
		return (exit_builtin(ac, av));
	return (-1);
}

// Free
void	free_command(char **command)
{
	int i;

	i = 0;
	while (command[i])
		ft_strdel(&command[i++]);
	free(command);
	command = NULL;
}