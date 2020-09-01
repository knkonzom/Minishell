#include "libft.h"

char	**ft_tabcopy(char **tab)
{
	char	**ret;
	int		size;
	int		i;

	size = ft_strlen_tab(tab);
	i = -1;
	if ((ret = (char **)malloc(sizeof(char *) * size + 1)) == NULL)
		return (NULL);
	while (++i < size)
		if ((ret[i] = ft_strdup(tab[i])) == NULL)
			return (NULL);
	ret[i] = NULL;
	return (ret);
}