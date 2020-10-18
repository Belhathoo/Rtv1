# include "./libft/libft.h"
# include <mlx.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include <float.h>
# include <pthread.h>

# include <stdio.h>

# define WIN_WIDTH  800
# define WIN_HEIGHT 400

# define RGB(x) (int)(255.99 * x)
# define RGBTOI(x, y, z) (x * 256 * 256 + y * 256 + z)


# define MLX_KEY_ESC 53

typedef struct  s_vec
{
    double e1;
    double e2;
    double e3;
}               t_vec;


typedef struct	s_ray
{
	t_vec		origin;
	t_vec		dir;
	double		t_min, t_max;
}				t_ray;

typedef	struct 	s_obj
{
	t_vec		center;
	double		size;
	// int			(*hit)();
	struct s_obj		*next;
}				t_object;


typedef struct	s_camera
{
	t_vec		origin;
	t_vec		lower_left_corner;
	t_vec		horizontal;
	t_vec		vertical;
	t_vec		lookat;
	t_vec		u;
	t_vec		v;
	t_vec		w;
	double		fov;
	double		half_h;
	double		half_w;
}				t_cam;

typedef	struct	s_hit_record
{
	double		t;
	t_vec		p;
	t_vec		normal;
}				t_hit_record;

typedef struct	s_ptr
{
	void		*win;
	void		*mlx;
	void		*img;
	int			*data;
	int			*bpp;
	int			*size;
	int			*endian;
	t_object	*o;
}               t_ptr;


t_vec		ft_vec(double x, double y, double z);
t_vec		ft_plus(t_vec a, t_vec b);
t_vec		ft_minus(t_vec a, t_vec b);
t_vec		ft_div(t_vec a, t_vec b);
t_vec		ft_produit(t_vec a, t_vec b);
t_vec		ft_unit_vec(t_vec a);
t_vec		ft_pro_k(t_vec a, double k);
t_vec		ft_div_k(t_vec a, double k);
double		ft_dot(t_vec a, t_vec b);
t_vec		ft_cross(t_vec a, t_vec b);
double		ft_length(t_vec a);
double		ft_lengthsquared(t_vec a);


t_ray   ft_ray(t_vec a, t_vec b);
t_vec   ray_fctn(t_ray r, float t);
void    ft_ray_tracer(t_object *o, t_ptr *p, double *x, double *y);

t_cam   cam_calcul(t_vec lookfrom, t_vec lookat, t_vec vup, double fov);
t_vec   ft_color(t_object *o, t_ray ray);

int    hit_sphere(t_object *sphere, t_ray r, t_hit_record rec);
int     ft_hit(t_object *o, t_ray r, t_hit_record rec);

int			ft_close(t_ptr *p);
int			ft_deal_key(int key, t_ptr *p);


void    ft_free_objects(t_object *o);


void    ft_print_vec(char *str,t_vec x);