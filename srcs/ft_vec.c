/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belhatho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 01:47:33 by belhatho          #+#    #+#             */
/*   Updated: 2020/10/18 01:47:35 by belhatho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./rtv1.h"

t_vec	ft_vec(double x, double y, double z)
{
	t_vec v;

	v.e1 = x;
	v.e2 = y;
	v.e3 = z;
	return (v);
}

t_vec	ft_plus(t_vec a, t_vec b)
{
	return (ft_vec(a.e1 + b.e1, a.e2 + b.e2, a.e3 + b.e3));
}

t_vec	ft_plus_k(t_vec a, double k)
{
	return (ft_vec(a.e1 + k, a.e2 + k, a.e3 + k));
}

t_vec	ft_minus(t_vec a, t_vec b)
{
	return (ft_vec(a.e1 - b.e1, a.e2 - b.e2, a.e3 - b.e3));
}

t_vec	ft_div(t_vec a, t_vec b)
{
	return (ft_vec(a.e1 / b.e1, a.e2 / b.e2, a.e3 / b.e3));
}

t_vec	ft_produit(t_vec a, t_vec b)
{
	return (ft_vec(a.e1 * b.e1, a.e2 * b.e2, a.e3 * b.e3));
}

t_vec	ft_unit_vec(t_vec a)
{
	float k;

	if (a.e1 == 0.0 && a.e2 == 0.0 && a.e3 == 0.0)
		return (ft_vec(0, 0, 0));
	k = 1.0 / sqrt(a.e1 * a.e1 + a.e2 * a.e2 + a.e3 * a.e3);
	return (ft_pro_k(a, k));
}

t_vec	ft_pro_k(t_vec a, double k)
{
	return (ft_vec(a.e1 * k, a.e2 * k, a.e3 * k));
}

t_vec	ft_div_k(t_vec a, double k)
{
	return (ft_vec(a.e1 / k, a.e2 / k, a.e3 / k));
}

double		ft_dot(t_vec a, t_vec b)
{
	return (a.e1 * b.e1 + a.e2 * b.e2 + a.e3 * b.e3);
}

t_vec	ft_cross(t_vec a, t_vec b)
{
	return (ft_vec((a.e2 * b.e3 - a.e3 * b.e2), -(a.e1 * b.e3 - a.e3 * b.e1),
				(a.e1 * b.e2 - a.e2 * b.e1)));
}

double		ft_length(t_vec a)
{
	return (sqrt(a.e1 * a.e1 + a.e2 * a.e2 + a.e3 * a.e3));
}

double		ft_lengthsquared(t_vec a)
{
	return (a.e1 * a.e1 + a.e2 * a.e2 + a.e3 * a.e3);
}
