/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_light.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcouto <lcouto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 17:06:37 by lcouto            #+#    #+#             */
/*   Updated: 2021/02/19 18:28:26 by lcouto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"



static int verify_digits(char **pnt_split, char **color_split ,char **info, t_rt *rt)
{
    int i;

    i = 0;
    while (i < 3)
    {
        if (skip_dot_verify_digits(color_split[i]) || skip_dot_verify_digits(pnt_split[i]))
            return (0);
        i++;
    }
    if (skip_dot_verify_digits(info[2]))
        return(0); 
    if (rt->light->light < 0 ||rt->light->light > 1)
        return (0);     
    
    return(1);
}


void parse_light(char **info, t_rt *rt)
{
    char **point_split;
    char **color_split;

    if (get_2darray_size(info) != 4)
    {
        errormsg("Wrong Input");  
    }
    point_split = ft_split(info[1], ',');
    color_split = ft_split(info[3], ',');
    rt->light->light = parse_double(info[2]);
	printf("\nlimi === %f\n",  rt->light->light );

    if (get_2darray_size(point_split) == 3 && get_2darray_size(color_split) == 3
        && verify_digits(point_split, color_split, info, rt)
    )
    {
        rt->light->pos.x = 	parse_double(point_split[0]);
        rt->light->pos.y  = parse_double(point_split[1]);
     	rt->light->pos.z = 	parse_double(point_split[2]);


 		rt->light->pos.w = 1;
        parse_color(info[3], &rt->light->color);

		printf("\n r = %d\n", rt->light->color.r);
		printf("\n r = %d\n", rt->light->color.g);
		printf("\n r = %d\n", rt->light->color.b);

		rt->light->intensity =  scalar_color(normalize_color(rt->light->color.r,rt->light->color.g, rt->light->color.b), rt->light->light);

		printf("\n r = %f\n", rt->light->intensity.r);
		printf("\n r = %f\n", rt->light->intensity.g);
		printf("\n r = %f\n",rt->light->intensity.b);
		printf("\n r = %f\n",rt->light->intensity.a);
		// exit(0);
    }
    else
    {
        free_2d_char_array(point_split);
        free_2d_char_array(color_split);
    }
    free_2d_char_array(point_split);
    free_2d_char_array(color_split);
}


