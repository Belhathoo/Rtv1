/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belhatho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 02:12:08 by belhatho          #+#    #+#             */
/*   Updated: 2019/05/21 19:52:27 by belhatho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	int		i;
	int		nbr;
	int		sgn;

	sgn = 1;
	i = 0;
	nbr = 0;
	while ((str[i] == '\n' || str[i] == '\t' || str[i] == '\r' ||
				str[i] == '\v' || str[i] == '\f' || str[i] == ' ') && str[i])
		i++;
	if ((str[i] == '-') || (str[i] == '+'))
	{
		if (str[i] == '-')
			sgn = -1;
		i++;
	}
	while ((*(str + i) >= '0') && (*(str + i) <= '9'))
	{
		nbr = nbr * 10 + *(str + i) - 48;
		i++;
	}
	return (sgn * nbr);
}
