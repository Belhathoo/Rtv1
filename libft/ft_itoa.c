/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belhatho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 02:20:50 by belhatho          #+#    #+#             */
/*   Updated: 2019/05/21 20:27:56 by belhatho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	int		size;
	int		test;
	int		str_size;
	char	*nbr;

	if (n == -2147483648)
	{
		nbr = ft_strdup("-2147483648");
		return (nbr);
	}
	size = ft_nbr_size(&n, &test, &str_size);
	nbr = (char *)malloc(sizeof(char) * (str_size + 2));
	if (nbr == NULL)
		return (NULL);
	if (test == 1)
		nbr[0] = '-';
	while (size != 0)
	{
		nbr[test++] = (n / size) + 48;
		n %= size;
		size /= 10;
	}
	nbr[test] = '\0';
	return (nbr);
}
