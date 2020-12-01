/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ray.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belhatho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 01:47:24 by belhatho          #+#    #+#             */
/*   Updated: 2020/10/18 01:47:25 by belhatho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "rtv1.h"

void	ft_mlx_putpixel(t_ptr *p, int x, int y, int color)
{
	if (x >= 0 && x < WIN_WIDTH && y >= 0 && y < WIN_HEIGHT)
		p->data[y * (int)WIN_WIDTH + x] = color;
}

t_ray   ft_ray(t_vec a, t_vec b)
{
    t_ray   r;

    r.origin = a;
    r.dir = b;
    return (r);
}

t_vec   ray_fctn(t_ray r, float t)
{
    t_vec res;

    res = ft_plus(r.origin, (ft_pro_k(r.dir, t)));
    return res;
}

t_ray   ft_ray_tracer(t_object *objs, t_ptr *p, double x, double y)
{
    t_cam   cam;   
    t_ray   r;

    cam = p->scene->camera;
    r.dir = ft_plus(ft_pro_k(cam.horizontal, x / IMG_WIDTH),
     ft_pro_k(cam.vertical, y / IMG_HEIGHT));
    r.dir = ft_plus(ft_minus(cam.lower_left_corner, cam.origin), dir);
    r.origin = cam.origin;

    return(ft_color(objs, r));

}
	t_color		c;
	t_ray		r;
	int			ss;

	c = COL(0, 0, 0);
	ss = -1;
	while (++ss < (int)scene->anti_a)
	{
		r = ft_get_ray(&scene->cam, col, row);
		c = ft_add_c(c, ft_raytrace_color(scene, &r, scene->object));
	}
	c = ft_div_kc(c, scene->anti_a);