/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcouto <lcouto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/11 15:06:06 by lcouto            #+#    #+#             */
/*   Updated: 2021/02/10 21:13:36 by lcouto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

static void		push_new_cylinder(t_cylinder *current, t_cylinder *new_cylinder)
{
	current->next = (t_cylinder*)ec_malloc(sizeof(t_cylinder));
	current->next->pos = new_cylinder->pos;
	current->next->norm = new_cylinder->norm;
	current->next->color = new_cylinder->color;
	current->next->transform = new_cylinder->transform;
	current->next->diameter = new_cylinder->diameter;
	current->next->radius = new_cylinder->radius;
	current->next->height = new_cylinder->height;
	current->next->phong = new_cylinder->phong;
	current->next->next = new_cylinder->next;
}

static void		push_cylinder(t_rt *rt, t_cylinder *new_cylinder)
{
	t_cylinder *current;

	current = rt->cylinder;
	new_cylinder->next = NULL;
	if (rt->qts.cy == 0)
	{
		rt->cylinder = (t_cylinder *)ec_malloc(sizeof(t_cylinder));
		rt->cylinder->pos = new_cylinder->pos;
		rt->cylinder->norm = new_cylinder->norm;
		rt->cylinder->diameter = new_cylinder->diameter;
		rt->cylinder->radius = new_cylinder->radius;
		rt->cylinder->height = new_cylinder->height;
		rt->cylinder->transform = new_cylinder->transform;
		rt->cylinder->phong = new_cylinder->phong;
		rt->cylinder->color = new_cylinder->color;
		rt->cylinder->next = new_cylinder->next;
		rt->qts.cy = rt->qts.cy + 1;
		return ;
	}
	while (current->next != NULL)
		current = current->next;
	push_new_cylinder(current, new_cylinder);
	rt->qts.cy = rt->qts.cy + 1;
}




static void store_in_scene_data(char **point_split, char **norm_vec, char **info, t_rt *rt)
{
	t_cylinder	*cylinder;
	t_phong		newphong;

	cylinder = (t_cylinder *)ec_malloc(sizeof(t_cylinder));
	newphong = default_phong();
	

    cylinder->pos.x = parse_double(point_split[0]);
    cylinder->pos.y = parse_double(point_split[1]);
    cylinder->pos.z  = parse_double(point_split[2]);
    cylinder->pos.w = 1;

    cylinder->norm.x = parse_double(norm_vec[0]);
  	cylinder->norm.y = parse_double(norm_vec[1]);
   	cylinder->norm.z = parse_double(norm_vec[2]);
	cylinder->norm.w = 0;

    parse_color(info[5], &cylinder->color);
	cylinder->phong = newphong;
	cylinder->phong.color = normalize_color(cylinder->color.r,cylinder->color.g, cylinder->color.b);
    cylinder->diameter = parse_double(info[3]);	
    cylinder->height = parse_double(info[4]);
    // cy->transform = identity_matrix();

	render_cylinder_transform(cylinder);
	push_cylinder(rt, cylinder);
	free(cylinder);
    // cy->material.shininess = 200.0;
    // cy->material.diffuse = 0.7;
    // cy->material.specular = 0.2;
    // cy->shape_name = "sp";
    // cy->material.ambient = scene_data->amb_ratio;
	// cy->material.color.r = cy->color.r/ 255;
	// cy->material.color.g = cy->color.g/ 255;
	// cy->material.color.b = cy->color.b/ 255;
    // transalation
    // scaling
    // rotation
    // skew
    // spehere.transform = transformed matrix
    // ft_lstadd_back(&scene_data->wrld.shapes,ft_lstnew(cy) );
}

static int verify_digits(char **nrm_vec_split, char **pnt_split, char **color_split ,char **info)
{
    int i;

    i = 0;
    while (i < 3)
    {
        if (skip_dot_verify_digits(nrm_vec_split[i]) || skip_dot_verify_digits(pnt_split[i]) || skip_dot_verify_digits(color_split[i]) )
            return (0);
        i++;
    }
    if (skip_dot_verify_digits(info[3]) || skip_dot_verify_digits(info[4]))
        return(0);    
    return(1);
}

void parse_cylinder(char **info, t_rt *rt)
{
    char **point_split;
    char **color_split;
    char **norm_vec;

    if (get_2darray_size(info) != 6)
    {
        errormsg("invalid input");
    }
    point_split = ft_split(info[1], ',');
    norm_vec = ft_split(info[2], ',');
    color_split = ft_split(info[5], ',');
    
    if (get_2darray_size(point_split) == 3 && get_2darray_size(norm_vec) == 3 && 
        get_2darray_size(color_split) == 3 &&  verify_digits(norm_vec, point_split ,color_split, info))
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


