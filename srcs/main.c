/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belhatho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 01:47:47 by belhatho          #+#    #+#             */
/*   Updated: 2020/10/18 01:47:49 by belhatho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./rtv1.h"

void	ft_mlx_launch(t_ptr *p)
{
    ft_init(p);
	p->mlx = mlx_init();
	p->win = mlx_new_window(p->mlx, WIN_WIDTH, WIN_HEIGHT, "RTv1");
    p->img = mlx_new_image(p->mlx, IMG_WIDTH, IMG_HEIGHT);
	p->data = (int*)mlx_get_data_addr(p->img, p->bpp, p->size, p->endian);
    p->scene->anti_a = 1;
}


int     main(int argc, char **argv)
{
    t_ptr *p;

   if (!(p = (struct s_ptr*)malloc(sizeof(struct s_ptr))))
        return (0);
    if (argc == 2)
        ft_parser(argv[1], p);
    else
        ft_fexit("usage: ./rtv1 scene_file\n", 0, &p);
    ft_mlx_launch(p);
    kick_off(p);    
    mlx_hook(p->win, 17, 0, ft_close, p);
    mlx_hook(p->win, 2, 0, ft_deal_key, p);
    mlx_loop(p->mlx);
    return (0);
}
