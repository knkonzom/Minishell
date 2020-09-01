#include "libft.h"

int	ft_strlen_tab(char **tab)
{
	int ret;

	ret = 0;
	while (*tab++)
		ret++;
	return (ret);
}