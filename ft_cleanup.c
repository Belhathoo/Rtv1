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


void        ft_exit(char *msg, int er, t_ptr **p)
{
    ft_putstr(ft_strjoin(err ? "error: " : "", display););
	ft_free_objects((*p)->scene->object);
	ft_free_lights((*p)->scene->light);
	free((*p)->scene);
	free(*p);
	exit(0);
}