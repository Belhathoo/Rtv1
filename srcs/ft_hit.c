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

int    ft_hit_sphere(t_object *sphere, t_ray *r, t_hit_record *rec)
{
    // t_vec       oc;
    // double      a, b, c, delta;
    // double      rec->sol[2];

    rec->oc = ft_minus(r->origin, sphere->pos);
    rec->coef[0] = ft_dot(r->dir, r->dir);
    rec->coef[1] = 2 * ft_dot(rec->oc, r->dir);
    rec->coef[2] = ft_dot(rec->oc, rec->oc) - pow(sphere->size, 2);
    rec->delta = rec->coef[1] * rec->coef[1] - 4 * rec->coef[0] * rec->coef[2];
    if (rec->delta > 0)
    {
        rec->sol[0] =  (-rec->coef[1] - sqrt(rec->delta)) / (2 * rec->coef[0]);
        rec->sol[1] =  (-rec->coef[1] + sqrt(rec->delta)) / (2 * rec->coef[0]);
        (rec->sol[0] > rec->sol[1]) ? rec->sol[0] = rec->sol[1] : 0;
        if (rec->sol[0] < rec->closest && rec->sol[0] > TMIN)
        {
            rec->t = rec->sol[0];
            rec->p = ray_fctn(r, rec->t);
            rec->normal = ft_div_k(ft_minus(rec->p, sphere->pos), sphere->size);
            return (1);
        }
    }
    return (0);
}

int     ft_hit(t_object *o, t_ray r, t_hit_record *rec, double tmax)
{
    t_hit_record    tmp_rec;
    int             hit_anything;
    double          closest;

    hit_anything = 0;
    rec->closest = tmax;
    while (o)
    {
        if (o->hit(o, &r, rec))
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
