/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belhatho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 12:20:00 by belhatho          #+#    #+#             */
/*   Updated: 2020/11/16 12:20:04 by belhatho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "rtv1.h"

void			ft_get_data(t_ptr *p, int fd)
{
	static int		cam_nbr;
	static int		obj_nbr;
	char			*line;

	get_next_line(fd, &line);
	while (get_next_line(fd, &line) > 0)
	{
		if (!ft_strncmp(line, "\t\"Camera\":", 10))
			ft_add_camera(p, fd, &line, cam_nbr++);
		else if (!ft_strncmp(line, "\t\"Object\": ", 11))
			ft_add_object(p, fd, &line, obj_nbr++);
		else if (!ft_strncmp(line, "\t\"Light\":", 9))
			ft_add_light(p, fd, &line);
		else if (!ft_strncmp(line, "]", 1))
			break ;
		else
			ft_fexit("unexpected data\n", 1, &p);
		free(line);
	}
	if (cam_nbr == 0 || obj_nbr == 0)
		ft_fexit("data missing - minimum \"1camera,1object\"\n", 1, &p);
}

void        ft_parser(char *file, t_ptr *p)
{
    int		fd;
	int		check;
	char	*txt;
	
	fd = open(file, O_RDONLY, !O_DIRECTORY);
	
	if ((fd = open(file, O_RDONLY)) == -1)
		ft_fexit(ft_strjoin(file, " : No Such File\n"), 1, &p);
	if (open(file, O_DIRECTORY) != -1)
		ft_fexit(ft_strjoin(file, " : Must Be a File\n"), 1, &p);
	txt = get_full_text(fd);
	close(fd);
	check = ft_check_brackets(txt);
	free(txt);
	if (check < 2)
		ft_fexit("brackets\n", 1, &p);
	fd = open(file, O_RDONLY);
	ft_get_data(p, fd);
	ft_check_data(p);
}