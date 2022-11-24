/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_camera.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcouto <lcouto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/06 22:00:00 by lcouto            #+#    #+#             */
/*   Updated: 2021/02/13 20:10:24 by lcouto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

// static void		push_new_camera(t_cam *current, t_cam *new_cam)
// {
// 	current->next = (t_cam *)ec_malloc(sizeof(t_cam));
// 	current->next->view = new_cam->view;
// 	current->next->pos = new_cam->pos;
// 	current->next->fov = new_cam->fov;
// 	current->next->half_height = new_cam->half_height;
// 	current->next->half_width = new_cam->half_width;
// 	current->next->pixel_size = new_cam->pixel_size;
// 	current->next->origin = new_cam->origin;
// 	current->next->transform = new_cam->transform;
// 	current->next->img = new_cam->img;
// 	current->next->address = new_cam->address;
// 	current->next->next = new_cam->next;
// }

// static void			push_camera(t_cam *head, t_cam *new_cam, t_rt *rt)
// {
// 	t_cam *current;

// 	current = head;
// 	new_cam->next = NULL;
// 	if (rt->qts.cam == 0)
// 	{
// 		head->view = new_cam->view;
// 		head->pos = new_cam->pos;
// 		head->fov = new_cam->fov;
// 		head->origin = new_cam->origin;
// 		head->half_height = new_cam->half_height;
// 		head->half_width = new_cam->half_width;
// 		head->pixel_size = new_cam->pixel_size;
// 		head->transform = new_cam->transform;
// 		head->img = new_cam->img;
// 		head->address = new_cam->address;
// 		head->next = new_cam->next;
// 		rt->qts.cam = rt->qts.cam + 1;
// 		return ;
// 	}
// 	while (current->next != NULL)
// 		current = current->next;
// 	push_new_camera(current, new_cam);
// 	rt->qts.cam = rt->qts.cam + 1;
// }

// static void		camera_loop(char *line, int i, int check, t_cam *cam)
// {
// 	while (line[i] != '\0')
// 	{
// 		if (line[i] == ' ')
// 			i++;
// 		else if ((line[i] >= '0' && line[i] <= '9') || line[i] == '-')
// 		{
// 			if (check == 0)
// 			{
// 				check = get_cam_view(line, check, i, cam);
// 				i = get_index(line, i);
// 			}
// 			else if (check == 3)
// 			{
// 				check = get_cam_pos(line, check, i, cam);
// 				i = get_index(line, i);
// 			}
// 			else if (check == 6)
// 			{
// 				check = get_cam_fov(line, check, i, cam);
// 				i = get_index(line, i);
// 			}
// 		}
// 		else if ((!(line[i] >= '0' && line[i] <= '9')) || (!(line[i] == ' ')))
// 			errormsg2(5);
// 	}
// }

void	print_matrix(double **mat, int col)
{
	int		i;
	int		j;

	i = 0;
	if (!mat)
		return ;
	while (i < col)
	{
		j = 0;
		while (j < col)
		{
			printf("| %lf\t", mat[i][j]);
			j++;
		}
		printf("|\n");
		i++;
	}
}
static int verify_digits(char **nrm_vec_split, char **pnt_split, char **info)
{
    int i;

    i = 0;
    while (i < 3)
    {
        if (skip_dot_verify_digits(nrm_vec_split[i]) || skip_dot_verify_digits(pnt_split[i]))
            return (0);
        i++;
    }
    if (skip_dot_verify_digits(info[3]))
        return (0);
    return(1);
}


void store_in_scene_data(t_rt *rt, char **point_split, char **norm_vec_split, char **info)
{
    rt->cam->view.x = parse_double(point_split[0]);
    rt->cam->view.y = parse_double(point_split[1]);
    rt->cam->view.z = parse_double(point_split[2]);
 	rt->cam->view.w = 1;

    rt->cam->pos.x = parse_double(norm_vec_split[0]);
    rt->cam->pos.y = parse_double(norm_vec_split[1]);
    rt->cam->pos.z = parse_double(norm_vec_split[2]);
	rt->cam->pos.w = 0;

    rt->cam->fov = parse_double(info[3]);
}

void parse_camera(char **info, t_rt *rt)
{
    char **point_split;
    char **norm_vec_split;
	// t_cam		*cam;
	t_matrix	transform;

	rt->cam = (t_cam *)ec_malloc(sizeof(t_cam));

    if (get_2darray_size(info) != 4)
    {
        errormsg("Wrong Input");  
    }
    point_split = ft_split(info[1], ',');
    norm_vec_split = ft_split(info[2], ',');
    if (get_2darray_size(point_split) == 3 && get_2darray_size(norm_vec_split) == 3 &&
        verify_digits(norm_vec_split, point_split , info))
    {        
        store_in_scene_data(rt, point_split, norm_vec_split, info);
		transform = view_transform(rt->cam->view, add_tuple(rt->cam->view,
		rt->cam->pos), cross_product(cross_product(rt->cam->pos,
		create_tuple(0, 1, 0, 0)), rt->cam->pos));
        // exit(0);
		rt->cam->transform = invert_matrix(transform);
		camera_pixel_size(rt->cam);
		rt->cam->origin = mult_matrix_tuple(rt->cam->transform, create_tuple(0, 0, 0, 1));
    }
    else
    {
        free_2d_char_array(point_split);
        free_2d_char_array(norm_vec_split);
          errormsg("Wrong Input");  
    }
    free_2d_char_array(point_split);
    free_2d_char_array(norm_vec_split);
}


// void			get_camera(char *line, t_rt *rt)
// {
// 	int			i;
// 	int			check;
// 	t_cam		*cam;
// 	t_matrix	transform;

// 	cam = (t_cam *)ec_malloc(sizeof(t_cam));
// 	check = 0;
// 	i = 1;
// 	camera_loop(line, i, check, cam);
	
// 	transform = view_transform(cam->view, add_tuple(cam->view,
// 		cam->pos), cross_product(cross_product(cam->pos,
// 		create_tuple(0, 1, 0, 0)), cam->pos));


// 	cam->transform = invert_matrix(transform);
// 	camera_pixel_size(cam);
// 	cam->origin = mult_matrix_tuple(cam->transform, create_tuple(0, 0, 0, 1));
// 	push_camera(rt->cam, cam, rt);
// 	free_matrix(transform);
// 	free(cam);
// }
