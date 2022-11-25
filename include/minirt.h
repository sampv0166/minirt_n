/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcouto <lcouto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/10 16:08:11 by lcouto            #+#    #+#             */
/*   Updated: 2021/02/15 13:12:02 by lcouto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <mlx.h>

# include "../libft/libft.h"
# include "vector.h"
# include "elements.h"
# include "ray.h"
# include <fcntl.h>
# include <stdlib.h>
# include <math.h>
# include <limits.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <ctype.h>
# include <stdio.h>

# define EPSILON 0.00001

# define WIDTH 640
# define HEIGHT 480

typedef struct		s_qts
{
	int				ambi;
	int				cam;
	int				lt;
	int				sp;
	int				pl;
	int				cy;
}					t_qts;

typedef struct		s_rt
{
	t_qts			qts;
	t_ambi			ambi;
	t_cam			*cam;
	t_light			*light;
	t_sphere		*sphere;
	t_plane			*plane;
	t_cylinder		*cylinder;
}					t_rt;

/*
** Holds values needed for MiniLibX's functions.
*/

typedef struct		s_mlx
{
	void			*mlx;
	void			*win;
	t_cam			*cam;
	t_cam			*begin;
	int				bpp;
	int				line_leng;
	int				endian;
	t_rt			*rt;
}					t_mlx;

/*
** Holds values for intersection pre-computation.
*/
typedef struct		s_comps
{
	double			t;
	t_polys			poly;
	t_tuple			position;
	t_light			*light;
	t_phong			phong;
	t_tuple			eye_vec;
	t_tuple			normal_vec;
	t_tuple			over_point;
	int				inside;
}					t_comps;



/*
** General parsing and error handling functions.
*/

void				init_rt(t_rt *rt);
void				errormsg(char *msg);
void				*ec_malloc(size_t size);
void				*ec_calloc(size_t n, size_t size);
void				parse_current_line(char *line, t_rt *rt);
char				*get_next_line(int fd);
char	*free_memmory(char **ptr);
size_t	get_current_line_size(char *saved_line);
double	ft_atof(char *s);
void		errormsg2(int num);
 int get_2darray_size(char **arr);
 int skip_dot_verify_digits(char *str);
 void free_2d_char_array(char **arr);
void parse_ambient_lighting(char **info, t_rt *rt);
double parse_double(char *str);
void parse_camera(char **info, t_rt *rt);
void parse_color(char *str, t_color *colors);
void parse_light(char **info, t_rt *rt);
void replace_tabs_and_newline(char *line);
void parse_sphere(char **info, t_rt *rt);
void parse_plane(char **info, t_rt *rt);
void parse_cylinder(char **info, t_rt *rt);





/*
** Camera parsing functions.
*/

void				get_camera(char *line, t_rt *rt);


/*
** Light parsing functions.
*/

void				get_light(char *line, t_rt *rt);

/*
** Sphere parsing functions.
*/

void				get_sphere(char *line, t_rt *rt);


/*
** Plane parsing functions.
*/

void				get_plane(char *line, t_rt *rt);


/*
** Cylinder parsing functions.
*/

void				get_cylinder(char *line, t_rt *rt);


int					double_equal(double a, double b);
double				radians_to_degrees(double rad);
double				degrees_to_radians(double degr);

/*
** Render utilities.
*/

void				ft_pixelput(t_cam *cam, int *coords,
					t_mlx *mlx, int color);
int					create_trgb(int t, int r, int g, int b);
int					close_program(void *ptr);
void				normalize_pixel_color(t_rgba *lt_output);
void				add_ambient_to_lights(t_rt *rt);
void				free_intersecs(t_intersec *intersec);

/*
** Core render functions.
*/

void				render(t_rt *rt, t_mlx *mlx);
void				raycaster(t_rt *rt, t_mlx *mlx, t_cam *cam);
void				cast_pixel(t_raycaster *rc, t_rt *rt,
					t_mlx *mlx, t_cam *cam);
t_tuple				normal_at(t_matrix transform, t_tuple point, t_polys poly);
t_tuple				normal_object_type(t_polys poly, t_tuple o_point);
t_tuple				reflect(t_tuple in, t_tuple normal);
t_rgba				lighting(t_comps comps, t_light *current_light,
					int in_shadow);
void				prepare_computations(t_comps *comps, t_rt *rt,
					t_raycaster *rc);
t_rgba				shade_hit(t_comps comps, t_rt *rt);
t_matrix			view_transform(t_tuple from, t_tuple to, t_tuple up);
void				camera_pixel_size( t_cam *cam);
t_ray				ray_for_pixel(t_cam *cam, int x, int y);
int					is_shadowed(t_comps comps, t_rt *rt, t_light *light);
void				create_image(t_rt *rt, t_mlx *mlx);

/*
** Polygon rendering functions.
*/

void				intersect_all_spheres(t_rt *rt, t_raycaster *rc);
void				intersect_all_polys(t_rt *rt, t_raycaster *rc);
void				intersect_all_planes(t_rt *rt, t_raycaster *rc);
void				intersect_all_squares(t_rt *rt, t_raycaster *rc);
void				intersect_all_cylinders(t_rt *rt, t_raycaster *rc);
void				render_sphere_transform(t_sphere *sphere);
void				render_plane_transform(t_plane *plane);
void				render_cylinder_transform(t_cylinder *cylinder);
void				intersect_caps(t_cylinder *cylinder, t_ray ray,
					t_intersec *head);
#endif
