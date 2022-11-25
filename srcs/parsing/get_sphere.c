/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcouto <lcouto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/10 17:42:20 by lcouto            #+#    #+#             */
/*   Updated: 2021/02/13 16:52:54 by lcouto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

static void		push_new_sphere(t_sphere *current, t_sphere *new_sphere)
{
	current->next = (t_sphere *)ec_malloc(sizeof(t_sphere));
	current->next->center = new_sphere->center;
	current->next->diameter = new_sphere->diameter;
	current->next->radius = new_sphere->radius;
	current->next->color = new_sphere->color;
	current->next->transform = new_sphere->transform;
	current->next->phong = new_sphere->phong;
	current->next->next = new_sphere->next;
}

static void		push_sphere(t_rt *rt, t_sphere *new_sphere)
{
	t_sphere *current;

	current = rt->sphere;
	new_sphere->next = NULL;
	if (rt->qts.sp == 0)
	{
		rt->sphere = (t_sphere *)ec_malloc(sizeof(t_sphere));
		rt->sphere->center = new_sphere->center;
		rt->sphere->diameter = new_sphere->diameter;
		rt->sphere->radius = new_sphere->radius;
		rt->sphere->color = new_sphere->color;
		rt->sphere->phong = new_sphere->phong;
		rt->sphere->transform = new_sphere->transform;
		rt->sphere->next = new_sphere->next;
		rt->qts.sp = rt->qts.sp + 1;
		return ;
	}
	while (current->next != NULL)
		current = current->next;
	push_new_sphere(current, new_sphere);
	rt->qts.sp = rt->qts.sp + 1;
}

static int verify_digits( char **pnt_split, char **color_split ,char **info)
{
    int i;

    i = 0;
    while (i < 3)
    {
        if (skip_dot_verify_digits(pnt_split[i]) || skip_dot_verify_digits(color_split[i]) )
            return (0);
        i++;
    }
    if (skip_dot_verify_digits(info[2]))
        return (0); 
    return(1);
}

// !REDUCE TO 25 LINES  - SAMAD
void parse_sphere(char **info, t_rt *rt)
{
    char **point_split;
    char **color_split;
	t_sphere	*sphere;
	t_phong		newphong;


    if (get_2darray_size(info) != 4)
	{
        errormsg("INVALID NUMBER OF VALUES FOR SPHERE");

	}
    
	sphere = (t_sphere *)ec_malloc(sizeof(t_sphere));
	newphong = default_phong();

    point_split = ft_split(info[1], ',');
    color_split = ft_split(info[3], ',');
    if (get_2darray_size(point_split) == 3 && get_2darray_size(color_split) == 3
        && verify_digits(point_split ,color_split, info) )
    {
        sphere->center.x = parse_double(point_split[0]);
        sphere->center.y  = parse_double(point_split[1]);
        sphere->center.z  = parse_double(point_split[2]);
		sphere->center.w  = 1;
    

			sphere->diameter = parse_double(info[2]);
		sphere->radius = parse_double(info[2]) / 2;

        parse_color(info[3], &sphere->color);
		sphere->phong = newphong;
		sphere->phong.color = normalize_color(sphere->color.r,sphere->color.g, sphere->color.b);
		render_sphere_transform(sphere);

		push_sphere(rt, sphere);
		free(sphere);

    }
    else
    {
        free_2d_char_array(point_split);
        free_2d_char_array(color_split);
        errormsg("Wrong Input");  
    }
    free_2d_char_array(point_split);
    free_2d_char_array(color_split);
}