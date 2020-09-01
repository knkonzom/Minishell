/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knkonzom <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/01 20:09:51 by knkonzom          #+#    #+#             */
/*   Updated: 2019/09/03 01:39:54 by knkonzom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	new_line(char **s, char **line, int fd, int ret)
{
	char	*temp;
	int		len;

	len = 0;
	while (s[fd][len] != '\n' && s[fd][len] != '\0')
		len++;
	if (s[fd][len] == '\n')
	{
		*line = ft_strsub(s[fd], 0, len);
		temp = ft_strdup(s[fd] + (len + 1));
		free(s[fd]);
		s[fd] = temp;
		if (s[fd][0] == '\0')
			ft_strdel(&s[fd]);
	}
	else if (s[fd][len] == '\0')
	{
		if (ret == BUFF_SIZE)
			return (get_next_line(fd, line));
		*line = ft_strdup(s[fd]);
		ft_strdel(&s[fd]);
	}
	return (1);
}

int			get_next_line(const int fd, char **line)
{
	static char	*s[255];
	char		buf[BUFF_SIZE + 1];
	char		*temp;
	int			ret;

	if (fd < 0 || line == NULL)
		return (-1);
	while ((ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[ret] = '\0';
		if (s[fd] == NULL)
			s[fd] = ft_strdup(buf);
		else
		{
			temp = ft_strjoin(s[fd], buf);
			free(s[fd]);
			s[fd] = temp;
		}
		if (ft_strchr(buf, '\n'))
			break ;
	}
	if (ret < 0)
		return (-1);
	else
		return ((ret == 0 && s[fd] == NULL) ? 0 : new_line(s, line, fd, ret));
}
