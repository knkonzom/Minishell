#include "libft.h"

int	ft_strucpy(char **dest, char *src, char c)
{
	int i;

	i = 0;
	while (src[i])
	{
		if (src[i] == c || src[i] == '\0')
			break ;
		i++;
	}
	if ((*dest = ft_strnew(i + 1)) == NULL)
		return (-1);
	ft_strncpy(*dest, src, i);
	return (i);
}