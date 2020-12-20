
#include "rtv1.h"

void			fft_get_data(t_ptr *p, char *txt)
{
	char	**file;
	
	if (!(p->scene = (struct s_scene*)malloc(sizeof(struct s_scene))))
		ft_fexit("Cannot allocate\n", 1, p);
	p->scene->obj = NULL;
	p->scene->light = NULL;

	file = ft_strsplit(txt, '}');
	
}