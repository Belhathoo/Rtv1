/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belhatho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 17:53:47 by belhatho          #+#    #+#             */
/*   Updated: 2020/11/21 17:54:03 by belhatho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

// void		ft_do_rot(t_ptr *p, t_vec *ret, char **each)
// {
// 	double		theta;

// 	theta = ft_atod(each[3]);
// 	if (theta < -180.0 || theta > 180.0 || ft_strlen(each[4]) != 1
// 		|| ((each[4][0] != 'x') && (each[4][0] != 'y') && (each[4][0] != 'z')))
// 	{
// 		ft_free_twodim(each);
// 		ft_fexit("Wrong rotation angle detected or axes type\n", 1, p);
// 	}
// 	ret->e1 = ft_atod(each[0]);
// 	ret->e2 = ft_atod(each[1]);
// 	ret->e3 = ft_atod(each[2]);
// 	*ret = ft_unit_vec(*ret);
// 	if (theta != 0.0)
// 	{
// 		if (each[4][0] == 'x')
// 			*ret = ft_rot_x(*ret, (theta * M_PI / 180.0));
// 		else if (each[4][0] == 'y')
// 			*ret = ft_rot_y(*ret, (theta * M_PI / 180.0));
// 		else
// 			*ret = ft_rot_z(*ret, (theta * M_PI / 180.0));
// 	}
// }

// int		ft_linetorot(t_ptr *p, char *line, t_vec *rot)
// {
// 	t_vec		ret;
// 	char		**each;
// 	char		*str;

// 	str = line;
// 	while (*str && *str != ':')
// 		str++;
// 	while (*str && *str != '"')
// 		str++;
// 	str++;
// 	str = ft_strsub(str, 0, ft_strlen(str) - 1);
// 	each = ft_strsplit(str, ' ');
// 	free(str);
// 	if (l != 5)
// 		ft_fexit("Must be five values for Rotation Data\n", 1, p);
// 	ft_do_rot(p, &ret, each);
// 	ft_free_twodim(each);
// 	return (1);
// }

int		ft_linetovec(t_ptr *p, char *str, t_vec *vec)
{
	t_vec		ret;
	char		**each;
	int 		i;
	size_t		l;
	
	i = 0;
	while (str[i] && str[i] != ':')
		i++;
	while (str[i] && str[i] != '"')
		i++;
	i++;
	if (i >= ft_strlen(str))
		return (0);
	each = ft_strsplit(ft_strsub(str, i, ft_strlen(str) - 1), ' ');
	l = ft_twodimlen(each);
	if (l < 3 || l > 4)
		return (0);
	else if (l == 3 && (each[2][0] == '\"' || !ft_strchr(each[2], '\"')))
		return (0);
	else if (l == 4 && each[3][0] != '\"')
			return (0);
	ret.e1 = ft_atod(each[0]);
	ret.e2 = ft_atod(each[1]);
	ret.e3 = ft_atod(each[2]);
	ft_free_twodim(each);
	*vec = ret;
	return (1);
}

int			ft_linetod(t_ptr *p, char *str, double *d)
{
	char		**each;
	int 		i;
	size_t		l;

	i = 0;
	while (str[i] && str[i] != ':')
		i++;
	while (str[i] && str[i] != '"')
		i++;
	i++;
	if (i >= ft_strlen(str))
		return (0);
	each = ft_strsplit(ft_strsub(str, i, ft_strlen(str) - 1), ' ');
	l = ft_twodimlen(each);
	if ((l == 1 &&(!ft_strchr(each[0], '\"') || each[0][0] == '\"'))
		|| (l == 2 && each[1][0] != '\"') || l != 1)
		return (0);
	*d = ft_atod(each[0]);
	ft_free_twodim(each);
	return (1);
}
