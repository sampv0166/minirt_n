/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_plane.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcouto <lcouto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/10 18:37:20 by lcouto            #+#    #+#             */
/*   Updated: 2021/02/13 16:56:20 by lcouto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

static void		push_new_plane(t_plane *current, t_plane *new_plane)
{
	current->next = (t_plane*)ec_malloc(sizeof(t_plane));
	current->next->pos = new_plane->pos;
	current->next->norm = new_plane->norm;
	current->next->color = new_plane->color;
	current->next->transform = new_plane->transform;
	current->next->phong = new_plane->phong;
	current->next->next = new_plane->next;
}

static void		push_plane(t_rt *rt, t_plane *new_plane)
{
	t_plane *current;

	current = rt->plane;
	new_plane->next = NULL;
	if (rt->qts.pl == 0)
	{
		rt->plane = (t_plane*)ec_malloc(sizeof(t_plane));
		rt->plane->pos = new_plane->pos;
		rt->plane->norm = new_plane->norm;
		rt->plane->color = new_plane->color;
		rt->plane->phong = new_plane->phong;
		rt->plane->transform = new_plane->transform;
		rt->plane->next = new_plane->next;
		rt->qts.pl = rt->qts.pl + 1;
		return ;
	}
	while (current->next != NULL)
		current = current->next;
	push_new_plane(current, new_plane);
	rt->qts.pl = rt->qts.pl + 1;
}

static int		loop_get_values(char *line, int i, int *chkptr,
t_plane *plane)
{
	if (*chkptr == 0)
	{
		*chkptr = get_plane_pos(line, *chkptr, i, plane);
		i = get_index(line, i);
	}
	else if (*chkptr == 3)
	{
		*chkptr = get_plane_norm(line, *chkptr, i, plane);
		i = get_index(line, i);
	}
	else if (*chkptr == 6)
	{
		*chkptr = get_plane_color(line, *chkptr, i, plane);
		i = get_index(line, i);
	}
	return (i);
}

static int		plane_loop(char *line, int i, int check, t_plane *plane)
{
	int *chkptr;

	chkptr = &check;
	while (line[i] != '\0' && check < 9)
	{
		if (line[i] == ' ')
			i++;
		else if ((line[i] >= '0' && line[i] <= '9') || line[i] == '-')
			i = loop_get_values(line, i, chkptr, plane);
		else if ((!(line[i] >= '0' && line[i] <= '9')) || (!(line[i] == ' ')))
			errormsg2(5);
	}
	return (i);
}


static int verify_digits(char **nrm_vec_split, char **pnt_split, char **color_split )
{
    int i;

    i = 0;
    while (i < 3)
    {
        if (skip_dot_verify_digits(nrm_vec_split[i]) || skip_dot_verify_digits(pnt_split[i]) || skip_dot_verify_digits(color_split[i]) )
            return (0);
        i++;
    }  
    return(1);
}


static void store_in_scene_data( char **point_split, char **norm_vec, char **info, t_rt *rt)
{
	t_plane		*plane;
	t_phong		newphong;

	plane = (t_plane *)ec_malloc(sizeof(t_plane));
	newphong = default_phong();

    plane->pos.x = parse_double(point_split[0]);
    plane->pos.y = parse_double(point_split[1]);
    plane->pos.z = parse_double(point_split[2]);
    plane->pos.w = 1;

    plane->norm.x= parse_double(norm_vec[0]);
    plane->norm.y= parse_double(norm_vec[1]);
   	plane->norm.z = parse_double(norm_vec[2]);
    plane->norm.x = 0;

    parse_color(info[3], &plane->color);
	plane->phong = newphong;
	plane->phong.color = normalize_color(plane->color.r,plane->color.g, plane->color.b);
	render_plane_transform(plane);
	push_plane(rt, plane);
}


void parse_plane(char **info, t_rt *rt)
{
    char **point_split;
    char **color_split;
    char **norm_vec;
    if (get_2darray_size(info) != 4)
    {
        errormsg("Wrong Input");  
    }
    point_split = ft_split(info[1], ',');
    norm_vec = ft_split(info[2], ',');
    color_split = ft_split(info[3], ',');
    if (get_2darray_size(point_split) == 3 && get_2darray_size(norm_vec) == 3 &&
        get_2darray_size(color_split) == 3 && verify_digits(norm_vec,point_split,color_split))
    {
        store_in_scene_data( point_split, norm_vec, info, rt);
    }
    else
    {
        free_2d_char_array(point_split);
        free_2d_char_array(norm_vec);
        free_2d_char_array(color_split);
        errormsg("Wrong Input");    
    }
    free_2d_char_array(point_split);
    free_2d_char_array(norm_vec);
    free_2d_char_array(color_split);
}

void			get_plane(char *line, t_rt *rt)
{
	int			i;
	int			check;
	t_plane		*plane;
	t_phong		newphong;

	plane = (t_plane *)ec_malloc(sizeof(t_plane));
	newphong = default_phong();
	check = 0;
	i = 2;
	i = plane_loop(line, i, check, plane);
	get_material(&newphong, line, i);
	plane->phong.specular = newphong.specular;
	plane->phong.shininess = newphong.shininess;
	plane->phong.reflect = newphong.reflect;
	render_plane_transform(plane);
	push_plane(rt, plane);
	free(plane);
}
