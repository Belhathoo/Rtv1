/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cleanup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belhatho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 12:24:56 by belhatho          #+#    #+#             */
/*   Updated: 2020/11/16 12:24:57 by belhatho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "rtv1.h"

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

void        ft_fexit(char *msg, int er, t_ptr **p)
{
    ft_putstr(ft_strjoin(err ? "error: " : "", display););
	ft_free_objects((*p)->scene->object);
	ft_free_lights((*p)->scene->light);
	free((*p)->scene);
	free(*p);
	exit(0);
}