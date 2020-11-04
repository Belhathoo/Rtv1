/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hook.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belhatho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 01:47:03 by belhatho          #+#    #+#             */
/*   Updated: 2020/10/18 01:47:05 by belhatho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "rtv1.h"

int			ft_close(t_ptr *p)
{
	mlx_destroy_image(p->mlx, p->img);
	mlx_destroy_window(p->mlx, p->win);
	// ft_free_objects(p->o);
	free(p->bpp);
	free(p->size);
	free(p->endian);
	free(p);
	p = NULL;
    exit (0);
}


int			ft_deal_key(int key, t_ptr *p)
{
	if (key == MLX_KEY_ESC)
		ft_close(p);
    return (key);
}



