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

static void		push_light(t_light *head, t_light *new_light, t_rt *rt)
{
	t_light *current;

	current = head;
	new_light->next = NULL;
	if (rt->qts.lt == 0)
	{
		head->pos = new_light->pos;
		head->light = new_light->light;
		head->color = new_light->color;
		head->intensity = new_light->intensity;
		head->next = new_light->next;
		rt->qts.lt = rt->qts.lt + 1;
		return ;
	}
	while (current->next != NULL)
		current = current->next;
	current->next = (t_light *)ec_malloc(sizeof(t_light));
	current->next->pos = new_light->pos;
	current->next->light = new_light->light;
	current->next->color = new_light->color;
	current->next->intensity = new_light->intensity;
	current->next->next = new_light->next;
	rt->qts.lt = rt->qts.lt + 1;
}

static int		get_light_light(char *line, int check, int i, t_light *light)
{
	double	lumi;

	while (line[i] != ' ' && line[i] != '\0')
	{
		if ((line[i] == '1' || line[i] == '0') && check == 3)
		{
			lumi = get_single_double(line, i);
			i = get_index(line, i);
			check++;
		}
		i++;
	}
	if (lumi > 1 || lumi < 0)
		errormsg2(16);
	// printf("\n%f\n", lumi);
	light->light = lumi;
	// exit(0);
	return (check);
}

static void		light_loop(char *line, int i, int check, t_light *light)
{
	while (line[i] != '\0')
	{
		if (line[i] == ' ')
			i++;
		else if ((line[i] >= '0' && line[i] <= '9') || line[i] == '-')
		{
			if (check == 0)
			{
				check = get_light_pos(line, check, i, light);
				i = get_index(line, i);
			}
			else if (check == 3)
			{
				check = get_light_light(line, check, i, light);
				i = get_index(line, i);
			}
			else if (check == 4)
			{
				check = get_light_color(line, check, i, light);
				i = get_index(line, i);
			}
		}
		else if ((!(line[i] >= '0' && line[i] <= '9')) || (!(line[i] == ' ')))
			errormsg2(5);
	}
}

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


void			get_light(char *line, t_rt *rt)
{
	int		i;
	int		check;
	t_light	*light;

	light = (t_light *)ec_malloc(sizeof(t_light));
	check = 0;
	i = 1;
	light_loop(line, i, check, light);
	light->intensity = scalar_color(normalize_color(light->color.r,
					light->color.g, light->color.b), light->light);
	push_light(rt->light, light, rt);
	free(light);
}
