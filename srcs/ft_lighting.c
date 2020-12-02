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

void   ft_diffuse(t_thread *th, t_light *l, t_vec lo, t_vec *diff)
{
    double  d;
    
    // l->brightness = 1.0;

    th->rec.curr_obj->kd = 1;
    d = th->rec.curr_obj->kd;
    d *= fmax(0.0, ft_dot(th->rec.normal, ft_unit_vec(lo)));
    *diff = ft_pro_k(l->color, d);
    ft_clamp(diff);
}

void   ft_ambient(t_light *l, t_object *o, t_vec *amb)
{
    o->ka = 0.25;
    *amb = ft_pro_k(l->color, o->ka * l->intensity);
    ft_clamp(amb);
}

void   ft_specular(t_thread *th, t_light *l, t_vec lo, t_vec *spec)
{
    double      s;
    t_vec       oc;
    t_vec       r;
    t_object    *o;

    o = th->rec.curr_obj;
    o->shininess = 30;
    oc = ft_minus(th->rec.normal, th->rec.ray->origin);
    oc = ft_unit_vec(oc);
    r = ft_unit_vec(ft_reflect(oc, th->rec.normal));
    s = th->rec.curr_obj->ks * l->intensity;
    s *= pow(fmax(0.0, ft_dot(oc, r)), o->shininess);
    *spec = ft_pro_k(l->color, s);
    ft_clamp(spec);
}

t_vec    ft_phong(t_thread *th, t_light *l, t_vec lo)
{
    t_vec   a_d_s[3];
    t_vec   phong_col;

    ft_ambient(l, th->rec.curr_obj, &a_d_s[0]);
    ft_diffuse(th, l, lo, &a_d_s[1]);
    ft_specular(th, l, lo, &a_d_s[2]);
    phong_col = ft_plus(ft_plus(a_d_s[0], a_d_s[1]), a_d_s[2]);
    phong_col = ft_produit(l->color, phong_col);
    ft_clamp(&phong_col);
    return (phong_col);
}

void    ft_lighting(t_thread *th, t_light *l, t_vec *c)
{
    t_object    *o;
    t_vec       l_vec;
    int         shade;

    o = th->rec.curr_obj;
    if (l == NULL)
        *c = ft_pro_k(o->color, o->ka);
    while (l != NULL)
    {
        shade = ft_shading(th, l);
        l_vec = ft_minus(l->pos, th->rec.p);
        *c = ft_plus(*c, ft_phong(th, l, l_vec));
        l = l->next;
    }
    // *c = o->color;
    *c = ft_produit(*c, o->color);
}