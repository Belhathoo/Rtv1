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

int     ft_shading(t_thread *th, t_light *l, t_vec lo)
{
    t_ray           sh_r;
    t_hit_record    rec;    
    t_object        *o;
    double          closest;

    o = th->rec.curr_obj;
    sh_r = ft_ray(th->rec.p, lo);
    closest = ft_length(sh_r.dir);
    sh_r.dir = ft_unit_vec(sh_r.dir);
    while (o != NULL)
    {
        if (o != th->rec.curr_obj)
            if (ft_hit(o, sh_r, &rec, closest))
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
    ia = 0.2;
    if (i)
        *col = ft_pro_k(th->rec.col, ia);
    else
        *col = ft_pro_k(ft_plus(th->p->scene->light->color, th->rec.col), ia); //
                
}

void   ft_diffuse(t_thread *th, t_light *l, t_vec lo, t_vec *diff)
{
    double  d;
    t_vec   c;

    th->rec.curr_obj->kd = 1.0; // --
    
    d = th->rec.curr_obj->kd * l->intensity;
    d *= ffmax(0.0, ft_dot(ft_unit_vec(lo), th->rec.normal));
    c = ft_produit(th->rec.curr_obj->color, l->color);
    c = ft_pro_k(ft_pro_k(c, d), l->f_att);
    *diff = ft_plus(*diff, c);
}

void   ft_specular(t_thread *th, t_light *l, t_vec lo, t_vec *spec)
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
    oc = ft_pro_k(ft_pro_k(oc, s), l->f_att);
    *spec = ft_plus(*spec, oc);
}

void    ft_phong(t_thread *th, t_light *l, t_vec lo, t_vec *d_s)
{
    l->f_att = ft_clamping(1 /
        ((ft_length(lo) + ft_length(th->rec.ray->dir)) * 0.02));
    ft_diffuse(th, l, lo,&d_s[0]);
    ft_specular(th, l, lo,&d_s[1]);
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
        shade = ft_shading(th, l, l->l_vec);
        if (shade == 0)
            ft_phong(th, l, l_vec, d_s);
        l = l->next;
    }
    *c = ft_plus(*c, ft_plus(d_s[0], d_s[1]));
}