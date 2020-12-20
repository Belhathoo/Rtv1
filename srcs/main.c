/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belhatho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 04:34:36 by belhatho          #+#    #+#             */
/*   Updated: 2020/12/09 04:34:37 by belhatho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		ft_init(t_ptr *p)
{
	p->img = NULL;
	p->mlx = NULL;
	p->data = NULL;
	p->win = NULL;
	p->scene->anti_a = 3;
	p->scene->amb = 0.85;
}

void		ft_mlx_launch(t_ptr *p)
{
	ft_init(p);
	p->mlx = mlx_init();
	p->win = mlx_new_window(p->mlx, IMG_WIDTH, IMG_HEIGHT, "RTv1");
	p->img = mlx_new_image(p->mlx, IMG_WIDTH, IMG_HEIGHT);
	p->data = (int*)mlx_get_data_addr(p->img, &p->bpp, &p->size, &p->endian);
}


void			add_camera(t_ptr *p, char **blc, int nb)
{
	t_cam		cam;
	int			i;
	int			j;
	
	(nb > 1) ? ft_fexit("One && only One Camera!\n", 1, p) : 0;
	i = 2;
	while (blc[i])
	{
		j = 0;
		while (blc[i][j] == ' ' || blc[i][j] == '\t')
			j++;
		if (i == 2 && ft_strncmp(blc[i] + j, "\"lookfrom\":", 11))
			ft_fexit("Camera syntax - lookfrom\n", 1, p);
		cam.origin = ft_linetovec(p, blc[2]);
		if (i == 3 && ft_strncmp(blc[i] + j, "\"lookat\":", 9))
			ft_fexit("Camera syntax - lookat\n", 1, p);
		if (i == 4 && ft_strncmp(blc[i] + j, "\"fov\":", 6))
			ft_fexit("Camera syntax - fov\n", 1, p);
		i++;
	}

	p->scene->camera = ft_cam_set(cam.origin, cam.lookat, cam.fov);
}

void			ft_affect_data(char	**txt, t_ptr *p)
{
	static int		cam_nbr = 0;
	static int		obj_nbr = 0;
	int		i;
	int		j;

	i = 0;
	while (txt[i])
	{
		j = 0;
		while (txt[i][j] && (txt[i][j] == '\n' ||txt[i][j] == '\t' || txt[i][j] == ' '))
			j++;
		if (txt[i][j] == ']' || j == ft_strlen(txt[i]))
			break;
		if ((txt[i]) && !ft_strcmp(txt[i] + j, "\"Camera\":"))
		{
			cam_nbr++;
			add_camera(p, txt, cam_nbr);
			i = i + 4;
		}
		else if ((txt[i]) && !ft_strncmp(txt[i] + j, "\"Object\":", 9))
			{printf("Obj\n"); i = i + 6;}
		else if ((txt[i]) && !ft_strcmp(txt[i] + j, "\"Light\":"))
			{printf("Light\n"); i = i + 4;}
		else
			ft_fexit("Unexpected Data!\n", 1, p);
		i++;
	}
	
}

void			get_data(t_ptr *p, char *txt)
{
	char	**file;
	char	**blc;
	int		i;
	
	 i = 0;
	if (!(p->scene = (struct s_scene*)malloc(sizeof(struct s_scene))))
		ft_fexit("Cannot allocate\n", 1, p);
	p->scene->obj = NULL;
	p->scene->light = NULL;

	file = ft_strsplit(txt, '}');
	while (file[i])
	{
		// printf("0. %s **\n", file[i]);
		if (ft_strcmp(file[i], "]") == 0)
			break;
		if (i == 0)
			blc = ft_strsplit(file[i] + 1, '\n');
		else
			blc = ft_strsplit(file[i], '\n');
		ft_affect_data(blc, p);
		i++;
	}
}

int			main(int argc, char **argv)
{
	t_ptr	p;

	if (argc == 2)
		ft_parser(argv[1], &p);
	else
		ft_fexit("usage: ./rtv1: 1_scene_file\n", 0, &p);
	// ft_mlx_launch(&p);
	// kick_off(&p);
	// mlx_hook(p.win, 17, 0, ft_close, &p);
	// mlx_hook(p.win, 2, 0, ft_deal_key, &p);
	// mlx_loop(p.mlx);
	return (0);
}
