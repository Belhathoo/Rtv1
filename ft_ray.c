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

void    ft_ray_tracer(t_object *objs, t_ptr *p, double x, double y)
{
    t_cam   cam;
    t_vec   d, vc;
    t_ray   r;
   
    int color;
    double u,v;
   
    u = (double)(x / WIN_WIDTH);
    v = (double)(y / WIN_HEIGHT);

    cam = p->scene->camera;
    d = ft_plus(ft_pro_k(cam.horizontal, u), ft_pro_k(cam.vertical, v));
    d = ft_plus(ft_minus(cam.lower_left_corner, cam.origin), d);
    r = ft_ray(cam.origin, d);
    vc = ft_color(objs, r);
    color = RGBTOI(RGB(vc.e1), RGB(vc.e2), RGB(vc.e3));
    ft_mlx_putpixel(p, x, y, color);
}
