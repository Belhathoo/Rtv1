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

char	*get_full_text(const int fd)
{
	char	*text;
	char	*tmp;
	int		ret;
	int		sum;

	sum = 0;
	text = (char*)malloc(BUFF_SIZE + 1);
	while ((ret = read(fd, &text[sum], BUFF_SIZE)))
	{
		sum += ret;
		text[sum] = '\0';
		tmp = ft_strdup(text);
		free(text);
		text = (char*)malloc(sum + BUFF_SIZE + 1);
		ft_strcpy(text, tmp);
		free(tmp);
	}
	text[sum] = '\0';
	return (text);
}

int			ft_check_brackets(char *s)
{
	int			b;
	int			i;

	i = 1;
	b = 0;
	while (s[i])
	{
		if (s[i] == '}')
			return (0);
		if (s[i] == '{')
		{
			b++;
			while (s[i])
			{
				i++;
				if (s[i] == '{')
					return (0);
				if (s[i] == '}')
					break ;
			}
		}
		i++;
	}
	return (s[0] && s[0] == '[' && s[i - 2] && s[i - 2] == ']' ? b : 0);
}

// void		ft_check_data(t_ptr *p)
// {
// 	t_object	*tmp;

// 	tmp = p->scene->object;
// 	if (p->scene->cam.fov < 0.0 || p->scene->cam.fov > 180.0)
// 		ft_free_exit("wrong field of view value\n", 1, &p);
// 	while (tmp)
// 	{
// 		if (tmp->size < 0.001 && tmp->hit != ft_hit_plane)
// 			ft_free_exit("wrong size detected\n", 1, &p);
// 		if (COL_TYPE(tmp->color.e1) || COL_TYPE(tmp->color.e2)
// 				|| COL_TYPE(tmp->color.e3))
// 			ft_free_exit("Wrong color format detected\n", 1, &p);
// 		tmp = tmp->next;
// 	}
// }

void			ft_get_data(t_ptr *p, int fd)
{
	static int		cam_nbr = 0;
	static int		obj_nbr = 0;
	char			*line;

	get_next_line(fd, &line);
	if(!(p->scene = (struct s_scene*)malloc(sizeof(struct s_scene))))
		ft_fexit("Cannot allocate\n", 1, &p);;
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
		// free(line);
	}
	if (cam_nbr == 0 || obj_nbr == 0)
		ft_fexit("Missing Data - Minimum \"1 camera & 1 object\"\n", 1, &p);
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
		ft_fexit("Brackets\n", 1, &p);
	fd = open(file, O_RDONLY);
	ft_get_data(p, fd);
	close(fd);
	// ft_check_data(p);
}