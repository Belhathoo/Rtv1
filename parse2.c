/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belhatho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 17:53:47 by belhatho          #+#    #+#             */
/*   Updated: 2020/11/21 17:54:03 by belhatho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "rtv1.h"

void		ft_do_rot(t_ptr *p, t_vector *ret, char **each)
{
	double		theta;

	theta = ft_atod(each[3]);
	if (theta < -180.0 || theta > 180.0 || ft_strlen(each[4]) != 1
			|| AXIS(each[4][0]))
	{
		ft_free_twodim(each);
		ft_free_exit("Wrong rotation angle detected or axes type\n", 1, &p);
	}
	ret->v1 = ft_atod(each[0]);
	ret->v2 = ft_atod(each[1]);
	ret->v3 = ft_atod(each[2]);
	*ret = ft_normalize(*ret);
	if (theta != 0.0)
	{
		if (each[4][0] == 'x')
			*ret = ft_rot_x(*ret, DEG_TO_RAD(theta));
		else if (each[4][0] == 'y')
			*ret = ft_rot_y(*ret, DEG_TO_RAD(theta));
		else
			*ret = ft_rot_z(*ret, DEG_TO_RAD(theta));
	}
}

t_vector	ft_linetorot(t_ptr *p, char **line, int free_it)
{
	t_vector	ret;
	char		**each;
	char		*str;

	str = *line;
	while (*str && *str != ':')
		str++;
	while (*str && *str != '"')
		str++;
	str++;
	str = ft_strsub(str, 0, ft_strlen(str) - 1);
	each = ft_strsplit(str, ' ');
	free(str);
	if (free_it)
		free(*line);
	if (ft_twodimlen(each) != 5)
		ft_free_exit("must be five values for Rotation data\n", 1, &p);
	ft_do_rot(p, &ret, each);
	ft_free_twodim(each);
	return (ret);
}

t_vector	ft_linetovec(t_ptr *p, char **line, int free_it)
{
	t_vector	ret;
	char		**each;
	char		*str;

	str = *line;
	while (*str && *str != ':')
		str++;
	while (*str && *str != '"')
		str++;
	str++;
	str = ft_strsub(str, 0, ft_strlen(str) - 1);
	each = ft_strsplit(str, ' ');
	free(str);
	if (free_it)
		free(*line);
	if (ft_twodimlen(each) != 3)
		ft_free_exit("must be three values for Vectors data\n", 1, &p);
	ret.v1 = ft_atod(each[0]);
	ret.v2 = ft_atod(each[1]);
	ret.v3 = ft_atod(each[2]);
	ft_free_twodim(each);
	return (ret);
}

t_color		ft_linetocol(t_ptr *p, char **line, int free_it)
{
	t_color		ret;
	char		**each;
	char		*str;

	str = *line;
	while (*str && *str != ':')
		str++;
	while (*str && *str != '"')
		str++;
	str++;
	str = ft_strsub(str, 0, ft_strlen(str) - 1);
	each = ft_strsplit(str, ' ');
	free(str);
	if (free_it)
		free(*line);
	if (ft_twodimlen(each) != 3)
		ft_free_exit("Must be three values for Colors data\n", 1, &p);
	ret.r = ft_atod(each[0]);
	ret.g = ft_atod(each[1]);
	ret.b = ft_atod(each[2]);
	ft_free_twodim(each);
	return (ret);
}

double		ft_linetod(t_ptr *p, char **line, int free_it)
{
	double		ret;
	char		**each;
	char		*str;

	str = *line;
	while (*str && *str != ':')
		str++;
	while (*str && *str != '"')
		str++;
	str++;
	str = ft_strsub(str, 0, ft_strlen(str) - 1);
	each = ft_strsplit(str, ' ');
	free(str);
	if (free_it)
		free(*line);
	if (ft_twodimlen(each) != 1)
		ft_free_exit("must be one value for such data\n", 1, &p);
	ret = ft_atod(each[0]);
	ft_free_twodim(each);
	return (ret);
}
