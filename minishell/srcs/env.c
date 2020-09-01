#include "minishell.h"

// Env utility duplicate
int		env_builtin(int ac, char **av)
{
	char	**tempenv;

	if (ac == 1)
		return (print_env(g_envp));
	else
	{
		tempenv = ft_tabcopy(g_envp);
		env_help(av, tempenv);
		free_command(tempenv);
	}
	return (1);
}

// Printing env
int		print_env(char **env)
{
	int i;
	// Print environment variables, return 1 if successful.
	i = -1;
	while (env[++i])
		if (ft_strcmp(env[i], "") != 0)
			ft_putendl(env[i]);
	return (1);
}

// Get content of a var in env.
// USes get_env_var function which returns position of *var in environment or -1 if it doesn't exist
char	*get_var_content(char *var)
{
	int		pos;
	char	**temp;
	char	*ret;


	if ((pos = get_env_var(g_envp, var)) == -1)
		return (NULL);
	temp = ft_strsplit(g_envp[pos], '=');
	ret = ft_strdup(temp[1]);
	free_command(temp);
	return (ret);
}

// Add var in env or replace one
char	**add_var(char **env, char *var)
{
	int		i;
	int		size;
	char	**new;

	// Function to add a var by allocatiing memory and duplicating/ replacing an existing var.
	// Create `new` to store var
	i = 0;
	size = ft_strlen_tab(env) + 1;
	if ((new = (char **)malloc(sizeof(char *) * size + 1)) == NULL)
		return (NULL);
	while (i < size - 1)
	{
		new[i] = ft_strdup(env[i]);
		i++;
	}
	new[i] = ft_strdup(var);
	new[i + 1] = NULL;
	// Free env pointer when finished.
	free_command(env);
	return (new);
}
