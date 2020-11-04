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

void		ft_free_objects(t_object *object)
{
	t_object	*obj;
	t_object	*tmp;

    obj = object;
	while (obj != NULL)
	{
		tmp = obj->next;
		free(obj);
		obj = tmp;
	}
}

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

void	ft_create_window(t_ptr *p)
{
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
            ft_ray_tracer(p->o, p, i, j);
            i++;   
        }
        j++;
    }
    // ft_free_objects(p->o);
    // p->o = NULL;
    mlx_put_image_to_window(p->mlx, p->win, p->img, 0, 0);
}

void    ft_create_obj(t_ptr *p)
{ 
    t_object        *tt = NULL;

    if (!(p->o = (t_object*)malloc(sizeof(struct s_obj))))
        return ;
    // tt = p->o;
    p->o->center = ft_vec(0, 0, -1);
    p->o->size = 0.5;
    // if(!(p->o->next = (t_object*)malloc(sizeof(struct s_obj))))
    //     return ;
    // p->o = p->o->next;
    // p->o->center = ft_vec(0, -101, -1);
    // p->o->size = 100;
    p->o->next = NULL;
    // p->o = tt;
}



int     main(int argc, char **argv)
{
    t_ptr *p;

   if (!(p = (struct s_ptr*)malloc(sizeof(struct s_ptr))))
        return (0);
   	ft_init(p);
	ft_create_window(p);
    ft_create_obj(p);
    ft_draw(p);    
    mlx_hook(p->win, 17, 0, ft_close, p);
    mlx_hook(p->win, 2, 0, ft_deal_key, p);
    mlx_loop(p->mlx);
}
