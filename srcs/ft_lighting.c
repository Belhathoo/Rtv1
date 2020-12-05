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
double      ffmax(double a, double b)
{
    return ((a >= b) ? a : b);
}
t_vec		ft_reflect(t_vec v, t_vec n)
{
	return (ft_minus(v, ft_pro_k(ft_pro_k(n, 2), ft_dot(v, n))));
}

int     ft_shading(t_thread *th, t_light *l, t_vec l_vec)
{
    t_ray           r;
    t_hit_record    rec;    
    t_object        *o;
    double          closest;

    o = th->rec.curr_obj;
    r.dir = l_vec;
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
    th->p->scene->amb = 0.5;
    th->rec.curr_obj->ka = 0.2; // --
    
    double  ia;

    ia = th->rec.curr_obj->ka * th->p->scene->amb;
    if (i)
        *col = ft_pro_k(th->rec.col, ia);
    else
        *col = ft_pro_k(ft_plus(th->p->scene->light->color, th->rec.col), ia); //
                
}

void   ft_diffuse(t_thread *th, t_light *l, t_vec lo, double f_att, t_vec *diff)
{
    double  d;
    t_vec   c;

    th->rec.curr_obj->kd = 1.0; // --
    
    d = th->rec.curr_obj->kd * l->intensity;
    d *= ffmax(0.0, ft_dot(ft_unit_vec(lo), th->rec.normal));
    c = ft_produit(th->rec.curr_obj->color, l->color);
    c = ft_pro_k(ft_pro_k(c, d), f_att);
    *diff = ft_plus(*diff, c);
}

void   ft_specular(t_thread *th, t_light *l, t_vec lo, double f_att, t_vec *spec)
{
    double      s;
    t_vec       oc;
    t_vec       refl;
    t_object    *o;

    o = th->rec.curr_obj;

    o->shininess = 90; // --
    o->ks = 0.8; // --
    
    refl = ft_unit_vec(ft_reflect(ft_unit_vec(lo), ft_unit_vec(th->rec.normal)));
    oc = ft_minus(th->rec.p, th->p->scene->camera.origin);
    s = pow(ffmax(0.0, ft_dot(refl, ft_unit_vec(oc))), o->shininess);
    s *= o->ks * l->intensity;
    oc = ft_produit(th->rec.curr_obj->color, l->color);
    oc = ft_pro_k(ft_pro_k(oc, s), f_att);
    *spec = ft_plus(*spec, oc);
}

void    ft_phong(t_thread *th, t_light *l, t_vec lo, t_vec *d_s)
{
    double  f_att;

    f_att = ft_clamping(1 / ((ft_length(lo) + ft_length(th->rec.ray->dir)) * 0.02));
    f_att = 1;
    ft_diffuse(th, l, lo, f_att, &d_s[0]);
    ft_specular(th, l, lo, f_att, &d_s[1]);
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
        l_vec = ft_minus(l->pos, th->rec.p);
        shade = ft_shading(th, l, l_vec);
        if (shade == 0)
            ft_phong(th, l, l_vec, d_s);
        l = l->next;
    }
    *c = ft_plus(*c, ft_plus(d_s[0], d_s[1]));
}