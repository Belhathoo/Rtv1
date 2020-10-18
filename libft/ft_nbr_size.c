/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbr_size.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belhatho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 02:21:17 by belhatho          #+#    #+#             */
/*   Updated: 2019/05/21 02:22:27 by belhatho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_nbr_size(int *n, int *test, int *str_size)
{
	int		size;
	int		copy;

	copy = *n;
	*test = 0;
	*str_size = 0;
	if (copy < 0)
	{
		*n *= (-1);
		copy *= (-1);
		(*test)++;
		(*str_size)++;
	}
	size = 1;
	while ((copy /= 10) != 0)
	{
		size *= 10;
		(*str_size)++;
	}
	return (size);
}
