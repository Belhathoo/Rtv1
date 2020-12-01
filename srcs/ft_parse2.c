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

int		ft_twodimlen(char **twodim)
{
	int		s;

	s = 0;
	while (*twodim++)
		s++;
	return (s);
}

void	ft_free_twodim(char **to_free)
{
	int		i;

	i = 0;
	while (to_free[i])
	{
		free(to_free[i]);
		i++;
	}
	free(to_free);
}

double		ft_atod(char *str)
{
	double		nbr;
	int			i;
	double		chfr;
	static int	signe;

	nbr = (double)ft_atoi(str);
	i = 0;
	chfr = 10;
	while ((str[i] == '\n') || (str[i] == ' ') || (str[i] == '\t')
			|| (str[i] == '\f') || (str[i] == '\v') || (str[i] == '\r'))
		i++;
	signe = str[i] == '-' ? 1 : 0;
	i = ((str[i] == '-') || (str[i] == '+')) ? i + 1 : i;
	while (str[i] && str[i++] != '.')
		i = i + 0;
	while (str[i] && str[i] >= 48 && str[i] <= 57)
	{
		nbr = nbr >= 0 && !signe ? nbr + (double)(str[i++] - 48) / chfr :
			nbr - (double)(str[i++] - 48) / chfr;
		chfr *= 10;
	}
	return (nbr);
}

void		ft_do_rot(t_ptr *p, t_vec *ret, char **each)
{
	double		theta;

	theta = ft_atod(each[3]);
	if (theta < -180.0 || theta > 180.0 || ft_strlen(each[4]) != 1
		|| ((each[4][0] != 'x') && (each[4][0] != 'y') && (each[4][0] != 'z')))
	{
		ft_free_twodim(each);
		ft_fexit("Wrong rotation angle detected or axes type\n", 1, &p);
	}
	ret->e1 = ft_atod(each[0]);
	ret->e2 = ft_atod(each[1]);
	ret->e3 = ft_atod(each[2]);
	*ret = ft_unit_vec(*ret);
	if (theta != 0.0)
	{
		if (each[4][0] == 'x')
			*ret = ft_rot_x(*ret, (theta * M_PI / 180.0));
		else if (each[4][0] == 'y')
			*ret = ft_rot_y(*ret, (theta * M_PI / 180.0));
		else
			*ret = ft_rot_z(*ret, (theta * M_PI / 180.0));
	}
}

t_vec	ft_linetorot(t_ptr *p, char **line, int free_it)
{
	t_vec	ret;
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
		ft_fexit("Must be five values for Rotation Data\n", 1, &p);
	ft_do_rot(p, &ret, each);
	ft_free_twodim(each);
	return (ret);
}

t_vec	ft_linetovec(t_ptr *p, char **line, int free_it)
{
	t_vec	ret;
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
		ft_fexit("must be three values for Vectors data\n", 1, &p);
	ret.e1 = ft_atod(each[0]);
	ret.e2 = ft_atod(each[1]);
	ret.e3 = ft_atod(each[2]);
	ft_free_twodim(each);
	return (ret);
}

t_vec		ft_linetocol(t_ptr *p, char **line, int free_it)
{
	t_vec		ret;
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
		ft_fexit("Must be three values for Colors data\n", 1, &p);
	ret.e1 = ft_atod(each[0]);
	ret.e2 = ft_atod(each[1]);
	ret.e3 = ft_atod(each[2]);
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
		ft_fexit("must be one value for such data\n", 1, &p);
	ret = ft_atod(each[0]);
	ft_free_twodim(each);
	return (ret);
}
