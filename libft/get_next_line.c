/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belhatho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/28 21:34:49 by belhatho          #+#    #+#             */
/*   Updated: 2019/07/29 00:01:26 by belhatho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_read_fd(char **save, char *buf, int fd)
{
	char	*tmp;
	int		nbr_oct;

	while ((nbr_oct = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[nbr_oct] = '\0';
		tmp = ft_strdup(*save);
		free(*save);
		*save = ft_strjoin(tmp, buf);
		free(tmp);
		if (ft_strchr(buf, '\n'))
			break ;
	}
	return (nbr_oct);
}

void	ft_affect_line(char **line, char **save, int i)
{
	char	*tmp;

	tmp = ft_strdup(*save);
	*line = ft_strsub(*save, 0, i);
	free(*save);
	if (tmp[i] == '\0')
		*save = ft_strdup("");
	else
		*save = ft_strdup(tmp + i + 1);
	free(tmp);
}

int		get_next_line(const int fd, char **line)
{
	static char	*save[4864];
	char		*buf;
	int			nbr_oct;
	int			i;

	i = 0;
	if (!(buf = ft_strnew(BUFF_SIZE + 1)) ||
			fd == -1 || fd > 4864 || !line || read(fd, buf, 0) < 0)
	{
		free(buf);
		return (-1);
	}
	if (save[fd] == NULL)
		save[fd] = ft_strnew(0);
	nbr_oct = ft_read_fd(&save[fd], buf, fd);
	free(buf);
	buf = NULL;
	if ((ft_strlen(save[fd]) == 0) && (nbr_oct == 0))
		return (0);
	while (save[fd][i] != '\0' && save[fd][i] != '\n')
		i++;
	ft_affect_line(line, &save[fd], i);
	return (1);
}
