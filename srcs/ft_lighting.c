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

/*
OBJ: bool islit, double ambient(ka)
LIT: float amb_intensity  float brightness
*/
t_vec		ft_reflect(t_vec v, t_vec n)
{
	return (ft_minus(v, ft_pro_k(ft_pro_k(n, 2), ft_dot(v, n))));
}

int     ft_shading(t_thread *th, t_light *l)
{
    t_ray           r;
    t_hit_record    rec;    
    t_object        *o;
    double          closest;

    o = th->rec.curr_obj;
    r.dir = ft_minus(l->pos, th->rec.p);
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

void   ft_ambient(_Bool i, t_thread *th, t_vec *col)
{
    th->p->scene->amb = 0.35;
    th->rec.curr_obj->ka = 1; // --
    
    double  ia;

    ia = th->rec.curr_obj->ka * th->p->scene->amb;
    if (i)
        *col = ft_pro_k(*col, ia);
    else
        *col = ft_pro_k(*col, ia); //ft_plus(th->p->scene->light->color,
                
}

void   ft_diffuse(t_thread *th, t_light *l, t_vec lo, t_vec *diff)
{
    double  d;
    
    th->rec.curr_obj->kd = 1; // --
    
    d = th->rec.curr_obj->kd;
    d *= fmax(0.0, ft_dot(th->rec.normal, ft_unit_vec(lo)));
    *diff = ft_plus(*diff, ft_pro_k(l->color, d));
}

void   ft_specular(t_thread *th, t_light *l, t_vec lo, t_vec *spec)
{
    double      s;
    t_vec       oc;
    t_vec       r;
    t_object    *o;

    o = th->rec.curr_obj;

    o->shininess = 30; // --
    o->ks = 0.6; // --
    
    oc = ft_minus(th->rec.normal, th->rec.ray->origin);
    oc = ft_unit_vec(oc);
    r = ft_unit_vec(ft_reflect(oc, th->rec.normal));
    s = o->ks * l->intensity;
    s *= pow(fmax(0.0, ft_dot(oc, r)), o->shininess);
    *spec = ft_plus(*spec, ft_pro_k(l->color, s));
}

void    ft_phong(t_thread *th, t_light *l, t_vec lo, t_vec *d_s)
{
    // ft_diffuse(th, l, lo, &d_s[0]);
    ft_specular(th, l, lo, &d_s[1]);
}

void    ft_lighting(t_thread *th, t_light *l, t_vec *c)
{
    t_object    *o;
    t_vec       l_vec;
    t_vec       d_s[2];
    int         shade;

    ft_ambient((l == NULL), th, c);
    d_s[0] = ft_vec(0.0, 0.0, 0.0);
    d_s[1] = ft_vec(0.0, 0.0, 0.0);
    o = th->rec.curr_obj;
    while (l != NULL)
    {
        shade = ft_shading(th, l);
        l_vec = ft_minus(l->pos, th->rec.p);
        if (shade == 0)
            ft_phong(th, l, l_vec, d_s);
        l = l->next;
    }
    *c = ft_plus(*c, ft_plus(d_s[0], d_s[1]));
}