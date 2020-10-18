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
        //res = ft_unit_vec(ft_minus(ray_fctn(ray, d), ft_vec(0, 0, -1)));
        return (ft_pro_k(ft_plus(rec.normal, ft_vec(1,1,1)), 0.5));
    }
    unit_dir = ft_unit_vec(ray.dir);
    d = 0.5 * (unit_dir.e2 + 1); 
    res = ft_plus(ft_pro_k(ft_vec(1, 1, 1), (1 - d)) , ft_pro_k(ft_vec(0.5, 0.7, 1), d));  
    return (res);
}

t_cam   cam_calcul(t_vec lookfrom, t_vec lookat, t_vec vup, double fov)
{
    t_cam   camera;
    double  theta;
    t_vec   llc, llc1;

    theta = fov * M_PI / 180;
    /*/theta = fov;
    camera.half_h = tan(theta / 2);
    camera.half_w = camera.half_h * WIN_WIDTH / WIN_HEIGHT;
    camera.w = ft_unit_vec(ft_minus(lookfrom, lookat));
    camera.u =  ft_unit_vec(ft_cross(vup, camera.w));
    camera.v = ft_cross(camera.w, camera.u);
    camera.origin = lookfrom;
    camera.horizontal = ft_pro_k(camera.u, 2 * camera.half_w);
    camera.vertical = ft_pro_k(camera.v, 2 * camera.half_h);
    llc = ft_minus(camera.origin, ft_pro_k(camera.u, camera.half_w));
    llc1 = ft_plus(ft_pro_k(camera.v, camera.half_h), camera.w);
    camera.lower_left_corner = ft_minus(llc, llc1);
    //camera.lower_left_corner = ft_vec(- camera.half_w, - camera.half_h, -1); 
    */
    camera.origin = ft_vec(0,0,0);
    camera.horizontal =  ft_vec(4,0,0);
    camera.vertical = ft_vec(0,4,0);
    camera.lower_left_corner = ft_vec(-2,-1,-1);//
    return (camera);
}
