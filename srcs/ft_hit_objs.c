/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hit_objs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belhatho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 23:33:48 by belhatho          #+#    #+#             */
/*   Updated: 2020/12/09 03:57:51 by belhatho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int			ft_hit_sphere(t_object *sphere, t_ray *r, t_record *rec)
{
	rec->oc = ft_minus(r->origin, sphere->pos);
	rec->coef[0] = ft_dot(r->dir, r->dir);
	rec->coef[1] = 2 * ft_dot(rec->oc, r->dir);
	rec->coef[2] = ft_dot(rec->oc, rec->oc) - pow(sphere->size, 2);
	rec->delta = rec->coef[1] * rec->coef[1] - 4 * rec->coef[0] * rec->coef[2];
	if (rec->delta > 0)
	{
		rec->sol[0] = (-rec->coef[1] - sqrt(rec->delta)) / (2 * rec->coef[0]);
		rec->sol[1] = (-rec->coef[1] + sqrt(rec->delta)) / (2 * rec->coef[0]);
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

int			ft_hit_plan(t_object *o, t_ray *r, t_record *rec)
{
	rec->t = ((ft_dot(o->rot, o->pos) - ft_dot(o->rot, r->origin))
			/ ft_dot(o->rot, r->dir));
	if (rec->t >= rec->closest || rec->t <= TMIN)
		return (0);
	rec->normal = o->rot;
	rec->p = ray_fctn(r, rec->t);
	return (1);
}

int			ft_hit_cylinder(t_object *o, t_ray *r, t_record *rec)
{
	rec->oc = ft_minus(r->origin, o->pos);
	rec->coef[0] = ft_dot(r->dir, r->dir) - pow(ft_dot(r->dir, o->rot), 2);
	rec->coef[1] = 2 * (ft_dot(r->dir, rec->oc) - (ft_dot(r->dir, o->rot)
				* ft_dot(rec->oc, o->rot)));
	rec->coef[2] = ft_dot(rec->oc, rec->oc) - pow(ft_dot(rec->oc, o->rot), 2)
		- o->size * o->size;
	rec->delta = rec->coef[1] * rec->coef[1] - 4 * rec->coef[0] * rec->coef[2];
	if (rec->delta >= 0)
	{
		rec->sol[0] = (-rec->coef[1] - sqrt(rec->delta)) / (2 * rec->coef[0]);
		rec->sol[1] = (-rec->coef[1] + sqrt(rec->delta)) / (2 * rec->coef[0]);
		rec->sol[0] = rec->sol[0] < rec->sol[1] ? rec->sol[0] : rec->sol[1];
		if (rec->sol[0] < rec->closest && rec->sol[0] > TMIN)
		{
			rec->t = rec->sol[0];
			rec->p = ray_fctn(r, rec->t);
			rec->normal = ft_unit_vec(ft_minus(ft_minus(rec->p, o->pos),
						ft_pro_k(o->rot, ft_dot(r->dir, o->rot)
							* rec->t + ft_dot(rec->oc, o->rot))));
			return (1);
		}
	}
	return (0);
}

int			ft_hit_cone(t_object *o, t_ray *r, t_record *rec)
{
	rec->oc = ft_minus(r->origin, o->pos);
	rec->coef[0] = ft_dot(r->dir, r->dir) - (1 + pow(tan(o->size), 2))
		* pow(ft_dot(r->dir, o->rot), 2);
	rec->coef[1] = 2 * (ft_dot(r->dir, rec->oc) - (1 + pow(tan(o->size), 2))
			* ft_dot(r->dir, o->rot) * ft_dot(rec->oc, o->rot));
	rec->coef[2] = ft_dot(rec->oc, rec->oc) - (1 + pow(tan(o->size), 2))
		* pow(ft_dot(rec->oc, o->rot), 2);
	rec->delta = rec->coef[1] * rec->coef[1] - 4 * rec->coef[0] * rec->coef[2];
	if (rec->delta < 0)
		return (0);
	rec->sol[0] = (-rec->coef[1] - sqrt(rec->delta)) / (2 * rec->coef[0]);
	rec->sol[1] = (-rec->coef[1] + sqrt(rec->delta)) / (2 * rec->coef[0]);
	rec->sol[0] = (rec->sol[0] > TMIN && rec->sol[0] < rec->sol[1]) ?
					rec->sol[0] : rec->sol[1];
	if (rec->sol[0] < rec->closest && rec->sol[0] > TMIN)
	{
		rec->t = rec->sol[0];
		rec->p = ray_fctn(r, rec->t);
		rec->tmp = ft_pro_k(o->rot, (ft_dot(r->dir, o->rot) * rec->t
					+ ft_dot(rec->oc, o->rot)));
		rec->tmp = ft_pro_k(rec->tmp, (1 + pow(tan(o->size), 2)));
		rec->normal = ft_unit_vec(ft_minus(ft_minus(rec->p, o->pos), rec->tmp));
		return (1);
	}
	return (0);
}
