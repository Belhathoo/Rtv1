/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belhatho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 12:37:52 by belhatho          #+#    #+#             */
/*   Updated: 2020/11/16 12:37:53 by belhatho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void			ft_add_camera(t_ptr *p, int fd, char **line, int t)
{
	t_cam		cam;

	(t > 0) ? ft_fexit("wrong camera number\n", 1, &p) : (t++);
	if (ft_strcmp(*line, "\t\"Camera\":") && FR(*line, 1))
		ft_fexit("Camera syntax\n", 1, &p);
	if (get_next_line(fd, line) > 0 && ft_strcmp(*line, "\t{") && FR(*line, 1))
		ft_fexit("Camera syntax - near to {\n", 1, &p);
	if (get_next_line(fd, line) > 0 && (ft_strncmp(*line, "\t\t\"lookfrom\": \""
					, 15) || line[0][ft_strlen(*line) - 1] != '"'))
		ft_fexit("Camera syntax - lookfrom\n", 1, &p);
	cam.origin = ft_linetovec(p, line, 1);
	if (get_next_line(fd, line) > 0 && (ft_strncmp(*line, "\t\t\"lookat\": \""
					, 13) || line[0][ft_strlen(*line) - 1] != '"'))
		ft_fexit("Camera syntax - lookat\n", 1, &p);
	cam.lookat = ft_linetovec(p, line, 1);
	if (get_next_line(fd, line) > 0 && (ft_strncmp(*line, "\t\t\"fov\": \""
					, 10) || line[0][ft_strlen(*line) - 1] != '"'))
		ft_fexit("Camera syntax - fov\n", 1, &p);
	cam.fov = ft_linetod(p, line, 1);
	if (get_next_line(fd, line) > 0 && ft_strcmp(*line, "\t}") && FR(*line, 1))
		ft_fexit("Camera syntax - near to }\n", 1, &p);
	p->scene->camera = cam_set(cam.origin, cam.lookat, cam.fov);
}

void			ft_get_object(t_ptr *p, t_object *obj, int fd, char **line)
{
	if (get_next_line(fd, line) > 0 && ft_strcmp(*line, "\t{") && FR(*line, 1))
		ft_fexit("Object syntax - near to {\n", 1, &p);
	if (get_next_line(fd, line) > 0 && (ft_strncmp(*line, "\t\t\"position\": \""
					, 15) || line[0][ft_strlen(*line) - 1] != '"'))
		ft_fexit("Object syntax - 1st param position\n", 1, &p);
	obj->pos = ft_linetovec(p, line, 1);
	if (get_next_line(fd, line) > 0 && (ft_strncmp(*line, "\t\t\"rotation\": \""
					, 15) || line[0][ft_strlen(*line) - 1] != '"'))
		ft_fexit("Object syntax - 2nd param rotation\n", 1, &p);
	obj->rot = ft_unit_vec(ft_linetorot(p, line, 1));
	if (get_next_line(fd, line) > 0 && (ft_strncmp(*line,
		"\t\t\"translation\": \"", 18) || line[0][ft_strlen(*line) - 1] != '"'))
		ft_fexit("Object syntax - 3rd param translation\n", 1, &p);
	obj->pos = ft_plus(obj->pos, ft_linetovec(p, line, 1));
	if (get_next_line(fd, line) > 0 && (ft_strncmp(*line, "\t\t\"color\": \""
					, 12) || line[0][ft_strlen(*line) - 1] != '"'))
		ft_fexit("Object syntax - 4th param color\n", 1, &p);
	obj->color = ft_linetocol(p, line, 1);
	if (get_next_line(fd, line) > 0 && (ft_strncmp(*line, "\t\t\"size\": \""
					, 11) || line[0][ft_strlen(*line) - 1] != '"'))
		ft_fexit("Object syntax - 5th param size\n", 1, &p);
	obj->size = ft_linetod(p, line, 1);
	if (get_next_line(fd, line) > 0 && ft_strcmp(*line, "\t}") && FR(*line, 1))
		ft_fexit("Object syntax - near to }\n", 1, &p);
}

void			ft_add_object(t_ptr *p, int fd, char **line, int t)
{
	t_object		*obj;
	t_object		*tmp;
	printf("LOLO\n");

	if (!(obj = (struct s_obj*)malloc(sizeof(struct s_obj))) && t < 0)
		ft_fexit("Cannot allocate\n", 1, &p);
	tmp = p->scene->obj;
	if (ft_strcmp(*line, C_S) && ft_strcmp(*line, C_CO) && ft_strcmp(*line, C_P)
			&& ft_strcmp(*line, C_CY) && FR(*line, 1))
		ft_fexit("object syntax - undefined object\n", 1, &p);
	if (!ft_strcmp(*line, C_S) && (obj->hit = ft_hit_sphere))
		obj->name = ft_strdup("SPHERE");
	else if (!ft_strcmp(*line, C_CY) && (obj->hit = ft_hit_sphere))
		obj->name = ft_strdup("CYLINDER");
	else if (!ft_strcmp(*line, C_CO) && (obj->hit = ft_hit_sphere))
		obj->name = ft_strdup("CONE");
	else if (!ft_strcmp(*line, C_P) && (obj->hit = ft_hit_sphere))
		obj->name = ft_strdup("PLANE");
	ft_get_object(p, obj, fd, line);
	p->scene->obj = obj;
	obj->next = tmp;
}

double		ft_clamping(double value)
{
	if (value < 0.0)
		value = 0.0;
	if (value > 1.0)
		value = 1.0;
	return (value);
}

void			ft_add_light(t_ptr *p, int fd, char **line)
{
	t_light			*light[2];

	if (!(light[0] = (struct s_l*)malloc(sizeof(struct s_l))))
		ft_fexit("Cannot allocate\n", 1, &p);
	light[1] = p->scene->light;
	if (ft_strcmp(*line, "\t\"Light\":") && FR(*line, 1))
		ft_fexit("Light syntax\n", 1, &p);
	if (get_next_line(fd, line) > 0 && ft_strcmp(*line, "\t{") && FR(*line, 1))
		ft_fexit("Light syntax - near to {\n", 1, &p);
	if (get_next_line(fd, line) > 0 && (ft_strncmp(*line, "\t\t\"position\": \""
				, 15) || line[0][ft_strlen(*line) - 1] != '"') && FR(*line, 1))
		ft_fexit("Light syntax - 1st param position\n", 1, &p);
	light[0]->pos = ft_linetovec(p, line, 1);
	if (get_next_line(fd, line) > 0 && (ft_strncmp(*line, "\t\t\"color\": \""
				, 12) || line[0][ft_strlen(*line) - 1] != '"') && FR(*line, 1))
		ft_fexit("Light syntax - 2nd param color\n", 1, &p);
	light[0]->color = ft_linetocol(p, line, 1);
	if (get_next_line(fd, line) > 0 && (ft_strncmp(*line,
		"\t\t\"intensity\": \"", 16) || line[0][ft_strlen(*line) - 1] != '"'))
		ft_fexit("Light syntax - 3d param intensity\n", 1, &p);
	light[0]->intensity = ft_clamping(ft_linetod(p, line, 1));
	if (get_next_line(fd, line) > 0 && ft_strcmp(*line, "\t}") && FR(*line, 1))
		ft_fexit("Light syntax - near to }\n", 1, &p);
	p->scene->light = light[0];
	light[0]->next = light[1];
}
