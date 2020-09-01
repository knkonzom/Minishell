#include "minishell.h"

// Returns the relative path of a binary
static char	*path_to_bin(char *path, char *bin)
{
	char *ret;
	char *tmp;

	tmp = ft_strjoin(path, "/");
	ret = ft_strjoin(tmp, bin);
	ft_strdel(&tmp);
	return (ret);
}

// Forking and executing a process
int			exec_command(char **command, char **env)
{
	pid_t	process;
	char	*bin;

	if ((bin = get_exec(env, command[0])) == NULL)
		return (print_error(command[0]));
	process = fork();
	signal(SIGINT, process_sighandler);
	if (process == 0)
		process = execve(bin, command, env);
	wait(&process);
	ft_strdel(&bin);
	return (1);
}

// Return content of the env var 'PATH' or NULL if there is none
char		**get_paths(char **env)
{
	char **tmp;
	char **ret;

	if (get_env_var(env, "PATH") == -1)
		return (NULL);
	if ((tmp = ft_strsplit(env[get_env_var(env, "PATH")], '=')) == NULL)
		return (NULL);
	if ((ret = ft_strsplit(tmp[1], ':')) == NULL)
	{
		free_command(tmp);
		return (NULL);
	}
	else
	{
		free_command(tmp);
		return (ret);
	}
}

// Searching in env for a binary or return NULL
char		*get_exec(char **env, char *path)
{
	char		**tmp;
	struct stat	s;
	int			i;
	int			size;
	char		*newpath;

	i = 0;
	if (stat(path, &s) == 0 && (s.st_mode & S_IFREG))
		return (ft_strdup(path));
	if ((tmp = get_paths(env)) == NULL)
		return (NULL);
	while (tmp[i])
		i++;
	size = i;
	i = -1;
	while (tmp[++i] && ((stat((newpath = path_to_bin(tmp[i], path)), &s)) == -1 || !(s.st_mode & S_IFREG)))
		ft_strdel(&newpath);
	free_command(tmp);
	if (i == size)
		return (NULL);
	return (newpath);
}