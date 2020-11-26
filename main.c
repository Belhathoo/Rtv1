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

void	ft_mlx_launch(t_ptr *p)
{
    ft_init(p);
	p->mlx = mlx_init();
	p->win = mlx_new_window(p->mlx, WIN_WIDTH, WIN_HEIGHT, "rtv1");
    p->img = mlx_new_image(p->mlx, WIN_WIDTH, WIN_HEIGHT);
	p->data = (int*)mlx_get_data_addr(p->img, p->bpp, p->size, p->endian);    
}

void    ft_draw(t_ptr *p)
{
    double i;
    double j;
    double u, v;

    j = 0;
    while (j <= WIN_HEIGHT - 1)
    {
        i = 0;
        while (i < WIN_WIDTH)
        {
            ft_ray_tracer(p->scene->obj, p, i, j);
            i++;   
        }
        j++;
    }
    mlx_put_image_to_window(p->mlx, p->win, p->img, 0, 0);
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
    // t_object *o;
    // o = p->scene->obj;
    // while(o)
    // {
    //     printf("NAME:\t%s\n", o->name);
    //     o = o->next;
    // }
    ft_mlx_launch(p);
    ft_draw(p);    
    mlx_hook(p->win, 17, 0, ft_close, p);
    mlx_hook(p->win, 2, 0, ft_deal_key, p);
    mlx_loop(p->mlx);
    return (0);
}
