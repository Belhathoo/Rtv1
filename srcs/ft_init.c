/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belhatho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 01:44:37 by belhatho          #+#    #+#             */
/*   Updated: 2020/12/02 01:44:47 by belhatho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		ft_init(t_ptr *p)
{
	p->img = NULL;
	p->mlx = NULL;
	p->data = NULL;
	p->win = NULL;
   	p->bpp = malloc(4);
	p->size = malloc(4);
	p->endian = malloc(4);
}

void		ft_adjustment(t_vec *c)
{
	c->e1 = ft_clamping(c->e1);
	c->e2 = ft_clamping(c->e2);
	c->e3 = ft_clamping(c->e3);
}

double			ft_clamping(double value)
{
	if (value < 0.0)
		value = 0.0;
	if (value > 1.0)
		value = 1.0;
	return (value);
}