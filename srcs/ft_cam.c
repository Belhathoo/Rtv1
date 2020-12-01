/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cam.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belhatho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 01:47:13 by belhatho          #+#    #+#             */
/*   Updated: 2020/10/18 01:47:16 by belhatho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "rtv1.h"

t_vec   ft_color(t_object *objs, t_ray ray)
{
    t_vec           unit_dir;
    t_hit_record    rec;
    double   d;
    t_vec   res;
    
    if ((d = ft_hit(objs, ray, &rec)) > 0)
        return (rec.curr_obj->color);
    // unit_dir = ft_unit_vec(ray.dir);
    // d = 0.5 * (unit_dir.e2 + 1); 
    // res = ft_plus(ft_pro_k(ft_vec(1, 1, 1), (1 - d)) , ft_pro_k(ft_vec(0.5, 0.7, 1), d));  
    res = ft_vec(0,0,0);
    return (res);
}

t_cam   cam_set(t_vec lookfrom, t_vec lookat, double fov)
{
    t_cam   cam;
    double  theta;
    t_vec   vup;
    t_vec   llc;

    vup = ft_unit_vec(ft_vec(0.001, 1, 0.001));
    theta = fov * M_PI / 180.0;
    cam.origin = lookfrom;
    cam.half_h = tan(theta / 2.0);
    cam.half_w = cam.half_h * (WIN_WIDTH / WIN_HEIGHT);
    cam.w = ft_unit_vec(ft_minus(lookat, lookfrom));
    cam.u =  ft_unit_vec(ft_cross(cam.w, vup));
    cam.v = ft_cross(cam.u, cam.w);
    cam.horizontal = ft_pro_k(cam.u, 2.0 * cam.half_w);
    cam.vertical = ft_pro_k(cam.v, 2.0 * cam.half_h);
    cam.lower_left_corner  = ft_minus(cam.origin, ft_plus(ft_pro_k(cam.v, cam.half_h),
        ft_pro_k(cam.u, cam.half_w)));
    cam.lower_left_corner = ft_plus(cam.lower_left_corner , cam.w);
    return (cam);
}