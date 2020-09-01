#include "minishell.h"

// Mallocing a copy of char **env
void	init_env(char **env)
{
	int i;

	// Allocating memory for global env var g_envp
	i = 0;
	while (env[i])
		i++;
	g_envp = (char **)malloc(sizeof(char *) * (i + 1));
	g_envp[i] = NULL;
	i = -1;
	while (env[++i])
		g_envp[i] = ft_strdup(env[i]);
	return ;
}

// Returns position of *var in **env or -1 if it doesn't exist
int		get_env_var(char **env, char *var)
{
	int		i;
	char	*current;

	i = 0;
	while (env[i] && ft_strcmp((current = get_var_name(env[i])), var) != 0)
	{
		ft_strdel(&current);
		i++;
	}
	if (env[i])
		ft_strdel(&current);
	if (env[i])
		return (i);
	else
		return (-1);
}

// Get var name from format 'FOO=BAR'
char	*get_var_name(char *var)
{
	char *ret;

	if (!var || !*var)
		return (NULL);
	if (var[0] == '=')
		return (var);
	ft_strucpy(&ret, var, '=');
	return (ret);
}
