/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lighting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belhatho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 01:52:44 by belhatho          #+#    #+#             */
/*   Updated: 2020/12/02 01:52:52 by belhatho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vec		ft_reflect(t_vec v, t_vec n)
{
	return (ft_sub(v, ft_pro_k(ft_pro_k(n, 2), ft_dot(v, n))));
}

int     ft_shading(t_thread *t, t_light *l)
{
    t_ray           r;
    t_hit_record    rec;    
    double          closest;

    r.dir = ft_minus(l->pos, th->rec.p)
    r.origin = th->rec.p;
    closest = ft_length(r.dir);
    while (o != NULL)
    {
        if (o != th->rec.curr_obj)
            if (ft_hit(o, r, &rec, closest))
                return (1);
        o = o->next;
    }
    return (0);
}

t_vec   ft_diffuse(t_thread *th, t_light *l, t_vec l_vec)
{
    t_vec   dif;
    double  d;
    
    dif = ft_unit_vec(l_vec);
    d = fmax(0.0, ft_dot(th->rec.n, dif));
    dif = ft_pro_k(ft_produit(th->rec.curr_obj->col, l->color), d);
    return (dif);
}

void    ft_lighting(t_thread *th, t_light *l, t_vec *col)
{
    t_object    *o;
    t_vec       l_vec;
    t_vec       dif;
    t_vec       spec;
    t_vec       amb;
    int         shade;

    o = th->rec.curr_obj;
    if (!l)
        *col = ft_pro_k(o->color, 0.25);
    while (l)
    {
        shade = ft_shading(t, l);
        l_vec = ft_minus(th->rec.p, l->pos);
        dif = ft_diffuse()    
        l = l->next;
    }
    

    // col = o->color;
    // return (col);
}