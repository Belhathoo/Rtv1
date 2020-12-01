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

int    ft_hit_sphere(t_object *sphere, t_ray r, t_hit_record *rec)
{
    t_vec       oc;
    double      a, b, c, delta;
    double      tmp[2];

    oc = ft_minus(r.origin, sphere->pos);
    a = ft_dot(r.dir, r.dir);
    b = 2 * ft_dot(oc, r.dir);
    c = ft_dot(oc, oc) - pow(sphere->size, 2);
    delta = pow(b, 2) - 4 * a * c;
    if (delta > 0)
    {
        tmp[0] =  (-b - sqrt(delta)) / (2 * a);
        tmp[1] =  (-b + sqrt(delta)) / (2 * a);
        (tmp[0] > tmp[1]) ? tmp[0] = tmp[1] : 0;
        if (tmp[0] < rec->closest && tmp[0] > TMIN)
        {
            rec->t = tmp[0];
            rec->p = ray_fctn(r, rec->t);
            rec->normal = ft_div_k(ft_minus(rec->p, sphere->pos), sphere->size);
            return (1);
        }
    }
    return (0);
}

int     ft_hit(t_object *o, t_ray r, t_hit_record *rec)
{
    t_hit_record    tmp_rec;
    int             hit_anything ;

    hit_anything = 0;
    rec->closest = DBL_MAX;
    while (o)
    {
        if (o->hit(o, r, rec))
        {
            hit_anything = 1;
            rec->closest = rec->t;
            rec->curr_obj = o;
            rec->ray = &r;
        }
        o = o->next;
    }
    return (hit_anything);
}
