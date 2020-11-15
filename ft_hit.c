/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belhatho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 01:46:53 by belhatho          #+#    #+#             */
/*   Updated: 2020/10/18 01:46:57 by belhatho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "rtv1.h"

int    hit_sphere(t_object *sphere, t_ray r, t_hit_record rec)
{
    t_vec       oc;
    double      a, b, c, delta;
    double      tmp = 0;

    oc = ft_minus(r.origin, sphere->center);
    a = ft_dot(r.dir, r.dir);
    b = 2 * ft_dot(oc, r.dir);
    c = ft_dot(oc, oc) - sphere->size*sphere->size;
    delta = b*b - 4*a*c;
    if (delta > 0)
    {
        tmp =  (-b - sqrt(delta)) / (2 * a);
        if (tmp < r.t_max && tmp > r.t_min)
        {
            rec.t = tmp;
            rec.p = ray_fctn(r, rec.t);
            rec.normal = ft_div_k(ft_minus(rec.p, sphere->center), sphere->size);
            return (1);
        }
        tmp =  (-b + sqrt(delta)) / (2 * a);
        if (tmp < r.t_max && tmp > r.t_min)
        {
            rec.t = tmp;
            rec.p = ray_fctn(r, rec.t);
            rec.normal = ft_div_k(ft_minus(rec.p, sphere->center), sphere->size);
            return (1);
        }
    }
    return (0);
}

int     ft_hit(t_object *o, t_ray r, t_hit_record rec)
{
    t_hit_record    tmp_rec;
    int             hit_anything = 0;
    double          closest_so_far = r.t_max;
    t_object        *tt = NULL;

    tt = o;
    while (o)
    {
        if (hit_sphere(o, r, tmp_rec))
        {
            hit_anything = 1;
            closest_so_far = tmp_rec.t;
            rec = tmp_rec;
        }
        o = o->next;
    }
    o = tt;
    return (hit_anything);
}
