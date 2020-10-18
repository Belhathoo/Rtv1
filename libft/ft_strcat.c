/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belhatho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 01:57:14 by belhatho          #+#    #+#             */
/*   Updated: 2019/05/20 02:01:13 by belhatho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *dest, const char *src)
{
	int		i;
	int		size;

	size = -1;
	i = 0;
	while (dest[i])
	{
		size++;
		i++;
	}
	i = 0;
	while (src[i])
	{
		dest[size + i + 1] = src[i];
		i++;
	}
	dest[size + i + 1] = '\0';
	return (dest);
}
