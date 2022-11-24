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

typedef struct		s_qts
{
	int				reso;
	int				ambi;
	int				cam;
	int				lt;
	int				sp;
	int				pl;
	int				sq;
	int				cy;
	int				tr;
}					t_qts;

typedef struct		s_rt
{
	t_qts			qts;
	t_reso			reso;
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
	t_tuple			reflect_vec;
	t_tuple			over_point;
	int				inside;
}					t_comps;



/*
** General parsing and error handling functions.
*/

void				init_rt(t_rt *rt);
void				errormsg(int errornum);
void				*ec_malloc(size_t size);
void				*ec_calloc(size_t n, size_t size);
void				rt_identify(char *line, t_rt *rt, t_mlx *mlx);
int					get_index(char *line, int i);
int					get_index_nocomma(char *line, int i);
double				get_coord(char *line, int i);
int					get_color(char *line, int i);
void				get_material(t_phong *phong, char *line, int i);
t_color				fill_color(int r, int g, int b);
double				get_single_double(char *line, int i);
void				comma_check(char *line, int idx, int error);

/*
** Window resolution parsing functions.
*/

void				get_resolution(char *line, t_rt *rt, t_mlx *mlx);

/*
** Ambient light and color parsing functions.
*/

void				get_ambient(char *line, t_rt *rt);
int					get_ambi_rgb(char *line, int check, int i, t_ambi *ambi);

/*
** Camera parsing functions.
*/

void				get_camera(char *line, t_rt *rt);
int					get_cam_view(char *line, int check, int i, t_cam *cam);
int					get_cam_pos(char *line, int check, int i, t_cam *cam);
int					get_cam_fov(char *line, int check, int i, t_cam *cam);

/*
** Light parsing functions.
*/

void				get_light(char *line, t_rt *rt);
int					get_light_pos(char *line, int check, int i, t_light *light);
int					get_light_color(char *line, int check, int i,
					t_light *light);

/*
** Sphere parsing functions.
*/

void				get_sphere(char *line, t_rt *rt);
int					get_sphere_center(char *line, int check, int i,
					t_sphere *light);
int					get_sphere_color(char *line, int check, int i,
					t_sphere *light);
int					get_sphere_diameter(char *line, int check, int i,
					t_sphere *sphere);

/*
** Plane parsing functions.
*/

void				get_plane(char *line, t_rt *rt);
int					get_plane_pos(char *line, int check, int i, t_plane *light);
int					get_plane_norm(char *line, int check, int i,
					t_plane *plane);
int					get_plane_color(char *line, int check, int i,
					t_plane *light);


/*
** Cylinder parsing functions.
*/

void				get_cylinder(char *line, t_rt *rt);
int					get_cylinder_pos(char *line, int check, int i,
					t_cylinder *light);
int					get_cylinder_color(char *line, int check, int i,
					t_cylinder *light);
int					get_cylinder_side(char *line, int check, int i,
					t_cylinder *cylinder);
int					get_cylinder_height(char *line, int check, int i,
					t_cylinder *cylinder);
int					get_cylinder_diameter(char *line, int check, int i,
					t_cylinder *cylinder);
int					get_cylinder_norm(char *line, int check, int i,
					t_cylinder *cylinder);


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
void				loading_bar(double percent, int total, t_rt *rt);
void				add_ambient_to_lights(t_rt *rt);
void				free_intersecs(t_intersec *intersec);

/*
** Core render functions.
*/

void				canvas(t_rt *rt, t_mlx *mlx);
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
void				camera_pixel_size(t_rt *rt, t_cam *cam);
t_ray				ray_for_pixel(t_cam *cam, int x, int y);
int					is_shadowed(t_comps comps, t_rt *rt, t_light *light);
void				create_images(t_rt *rt, t_mlx *mlx);

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
