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
    d = ft_hit(objs, ray, rec);
    if (d > 0)
    {
        res = ft_unit_vec(ft_minus(ray_fctn(ray, d), ft_vec(0, 0, -1)));
        return (ft_pro_k(ft_plus(res, ft_vec(1,1,1)), 0.5));
    }
    unit_dir = ft_unit_vec(ray.dir);
    d = 0.5 * (unit_dir.e2 + 1); 
    res = ft_plus(ft_pro_k(ft_vec(1, 1, 1), (1 - d)) , ft_pro_k(ft_vec(0.5, 0.7, 1), d));  
    return (res);
}

t_cam   cam_set(t_vec lookfrom, t_vec lookat, double fov)
{
    t_cam   cam;
    double  theta;
    t_vec   vup;
    t_vec   llc, llc1;

    // vup = ft_unit_vec(ft_vec(0.001, 1, 0.001));
    // theta = fov * M_PI / 180;
    // //theta = fov;
    // cam.half_h = tan(theta / 2);
    // cam.half_w = cam.half_h * (WIN_WIDTH / WIN_HEIGHT);
    // cam.w = ft_unit_vec(ft_minus(lookat, lookfrom));
    // cam.u =  ft_unit_vec(ft_cross(vup, cam.w));
    // cam.v = ft_cross(cam.w, cam.u);
    // cam.origin = lookfrom;
    // cam.horizontal = ft_pro_k(cam.u, 2.0 * cam.half_w);
    // cam.vertical = ft_pro_k(cam.v, 2.0 * cam.half_h);
    // llc = ft_minus(cam.origin, ft_plus(ft_pro_k(cam.v, cam.half_h),\
    // ft_pro_k(cam.u, cam.half_w)));
    // //llc1 = ft_plus(ft_pro_k(cam.v, cam.half_h), cam.w);
    // cam.lower_left_corner = ft_plus(llc, cam.w);
    // cam.lower_left_corner = ft_vec(- cam.half_w, - cam.half_h, -1); 
    cam.origin = ft_vec(0,0,0);
    cam.horizontal =  ft_vec(4,0,0);
    cam.vertical = ft_vec(0,4,0);
    cam.lower_left_corner = ft_vec(-2,-1,-1);
    return (cam);
}
