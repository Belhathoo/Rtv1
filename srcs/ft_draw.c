/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belhatho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 23:48:34 by belhatho          #+#    #+#             */
/*   Updated: 2020/11/30 23:48:42 by belhatho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void    *ft_draw(t_thread *thread)
{
    double  i;
    double  j;
    t_vec   color;
    int     c;

    j = IMG_HEIGHT;
    while (--j >= 0)
    {
        i = (int)(thread->i * IMG_WIDTH / NBTHREAD) - 1;;
        while (++i < (int)((thread->i + 1) * IMG_WIDTH / NBTHREAD))
        {
            color = ft_ray_tracer(thread->p->scene->obj, thread->p, i, j);
            c = RGBTOI(RGB(color.e1), RGB(color.e2), RGB(color.e3));
            ft_mlx_putpixel(thread->p, i, IMG_HEIGHT - j, c);  
        }
    }
    pthread_exit(NULL);
}

void		kick_off(t_ptr *p)
{
	pthread_t	thread[NBTHREAD];
	t_thread	div[NBTHREAD];
	int			i;

	i = -1;
	while (++i < NBTHREAD)
	{
		div[i].i = i;
		div[i].p = p;
		pthread_create(&thread[i], NULL, (void*)ft_draw, &div[i]);
	}
	while (--i >= 0)
		pthread_join(thread[i], NULL);
    mlx_put_image_to_window(p->mlx, p->win, p->img, 0, 0);
}

