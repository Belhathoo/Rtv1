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
            ft_ray_tracer(p->o, p, &i, &j);
            i++;   
        }
        j++;
    }
    mlx_put_image_to_window(p->mlx, p->win, p->img, 0, 0);
}

t_object    *ft_create_obj(void)
{
    t_object        *o; 
    t_object        *tt = NULL;

    if (!(o = (t_object*)malloc(sizeof(struct s_obj))))
        return (NULL) ;
    tt = o;
    o->center = ft_vec(0, 0, -1);
    o->size = 0.5;
    if(!(o->next = (t_object*)malloc(sizeof(struct s_obj))))
        return (NULL);
    o = o->next;
    o->center = ft_vec(0, -100.5, -1);
    o->size = 100;
    o->next = NULL;
    o = tt;
    return (o);
}



int     main(int argc, char **argv)
{
    t_ptr *p;

   if (!(p = (struct s_ptr*)malloc(sizeof(struct s_ptr))))
        return (0);
   	ft_init(p);
	ft_create_window(p);
    p->o = ft_create_obj();
    ft_draw(p);    
    mlx_hook(p->win, 17, 0, ft_close, p);
    mlx_hook(p->win, 2, 0, ft_deal_key, p);
    mlx_loop(p->mlx);
}
