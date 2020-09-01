#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <sys/stat.h>
# include <dirent.h>
# include <string.h>
# include <errno.h>
# include <signal.h>
# include "libft.h"
# include "get_next_line.h"

# define EXIST_ERROR 1
# define TYPE_ERROR 2


// Defining global var for environnement copy.
char	**g_envp;

void	minishell(void);
void	print_prompt(void);
int		is_builtin(int ac, char **av);
void	free_command(char **command);

int		env_builtin(int ac, char **av);
int		print_env(char **env);
int		env_error(char *arg);
char	*get_var_content(char *var);
char	**add_var(char **env, char *var);

void	set_env(char *var, char *content);
char	**replace_var(char **env, char *var);
int		setenv_builtin(int ac, char **av);

int		unsetenv_builtin(int ac, char **av);

int		cd_builtin(int ac, char **av);

int		echo_builtin(int ac, char **av);

void	init_env(char **env);
int		get_env_var(char **env, char *var);
char	*get_var_name(char *var);

char	**env_help(char **av, char **tmpenv);
char	**parse_command(char *str);

int		exit_builtin(int ac, char **av);
void	exit_error(int no, char *arg);

int		exec_command(char **command, char **env);
char	**get_paths(char **env);
char	*get_exec(char **env, char *path);


int		print_error(char *command);

void	signal_handler(int signo);
void	process_sighandler(int signo);

#endif