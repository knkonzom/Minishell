#include "minishell.h"

// Help function needed to pass 25line norm rule
char			**env_help(char **av, char **tempenv)
{
	char	*tmp;
	int		err;
	int		i;

	i = -1;
	err = 0;
	while (av[++i])
	{
		if (ft_strchr(av[i], '='))
			tempenv = replace_var(tempenv, av[i]);
		else if ((tmp = get_exec(tempenv, av[i])) != NULL)
		{
			err = exec_command(&av[i], tempenv);
			ft_strdel(&tmp);
			break ;
		}
		else
			err = env_error(av[i]);
		if (!ft_strchr(av[i], '='))
			err = 1;
	}
	if (err == 0)
		print_env(tempenv);
	return (tempenv);
}

// Counts how many arguments there are without spaces and '\t'.
static int		count_args(char *s)
{
	int words;
	int i;

	i = 0;
	words = 0;
	while (s[i])
	{
		if ((s[i] != ' ' && s[i] != '\t') && ((s[i - 1] == ' ' || s[i - 1] == '\t') || i == 0))
			words++;
		i++;
	}
	return (words);
}

// Return the size until next ' ' or '\t' for malloc
static int		arg_len(char *s)
{
	int len;

	len = 0;
	while (*s && (*s != ' ' && *s != '\t'))
	{
		len++;
		s++;
	}
	return (len);
}

// Command parser
char			**parse_command(char *str)
{
	int		tab_size;
	char	**tab;
	int		i;

	if (!str)
		return (NULL);
	i = 0;
	// Count args using count_args func.
	// Malloc for number of args.
	tab_size = count_args(str);
	if ((tab = (char **)malloc(sizeof(char *) * tab_size + 1)) == NULL)
		return (NULL);
	while (tab_size--)
	{
		while ((*str == ' ' || *str == '\t') && *str)
			str++;
		// ft_strsub counts total number of args in input str
		if ((tab[i++] = ft_strsub(str, 0, arg_len(str))) == NULL)
			return (NULL);
		str += arg_len(str);
	}
	tab[i] = NULL;
	// Return command array.
	return (tab);
}