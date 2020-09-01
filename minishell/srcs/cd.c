#include "minishell.h"

// Change CWD - updating cwd.
static void	update_cwd(char *cwd)
{
	char buf[4096];
	char *content;

	// getcwd is used to copy the pathname of CWD
	// to array pointed to by buf, of size 4096.
	getcwd(buf, 4096);
	// PWD adds var name "PWD" to buf.
	set_env("PWD", buf);
	if (!cwd)
	{
		// if !cwd, chdir to home var and free mem.
		chdir((content = get_var_content("HOME")));
		ft_strdel(&content);
	}
	else
		chdir(cwd); 
	getcwd(buf, 4096);
	set_env("OLDPWD", (content = get_var_content("PWD")));
	ft_strdel(&content);
	set_env("PWD", buf);
}

// Check if path is a directory.
static int	is_dir(char *path)
{
	struct stat s;

	// Stat gets info about file pointed to by s.
	// S_IFDIR checks whether is a directory.
	stat(path, &s);
	if (s.st_mode & S_IFDIR)
		return (1);
	return (0);
}

// Used to handle `~` when parsing.
static char	*parse_path(char *path)
{
	char *ret;
	char *temp;

	if (path[0] == '~')
	{
		// If cd ~, home dir temporarily stored in temp.
		temp = get_var_content("HOME");
		ret = ft_strjoin(temp, &path[1]);
		ft_strdel(&temp);
	}
	else
		ret = ft_strdup(path);
	return (ret);
	// Return home dir if ~ is path[0]
	// If not proceed to dup path and return it
}

// Print CD errrors.
static void	cd_error(int no, char *arg)
{
	if (no == EXIST_ERROR)
	{
		// Print if dir/file exists by using predefined constants
		ft_putstr_fd("cd: ", STDERR_FILENO);
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
	}
	else if (no == TYPE_ERROR)
	{
		// Print if dir exists by using predefined constants
		ft_putstr_fd("cd: ", STDERR_FILENO);
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd(": Not a directory\n", STDERR_FILENO);
	}
}

// Clone of `cd` command.
int			cd_builtin(int ac, char **av)
{
	char	*parsed;
	char	*temp;

	if (ac == 1)
		update_cwd(NULL);
	else
	{
		parsed = parse_path(av[1]);
		if (!ft_strcmp(av[1], "-"))
		{
			update_cwd((temp = get_var_content("OLDPWD")));
			ft_strdel(&temp);
			ft_putendl((temp = get_var_content("PWD")));
			ft_strdel(&temp);
		}
		else if (access(parsed, F_OK) == -1)
			cd_error(EXIST_ERROR, av[1]);
		else if (!is_dir(parsed))
			cd_error(TYPE_ERROR, av[1]);
		else
			update_cwd(parsed);
		ft_strdel(&parsed);
	}
	return (1);
}