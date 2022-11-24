/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ambient.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcouto <lcouto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 15:52:38 by lcouto            #+#    #+#             */
/*   Updated: 2021/02/19 18:28:16 by lcouto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

static double get_decimal_point(double res, char *str)
{
    double num;
    double divider;
    double dec_val;

    dec_val = 0.0;
    num = 0.0;
    divider = 10;
    while (*str && ft_isdigit(*str))
    {
        dec_val = *str - '0';
        num = num + dec_val / divider; 
        divider = divider * 10;
        str++;
    }
    return (res + num);
}


double parse_double(char *str)
{
    double res;
    int sign;
    
    res = (double) ft_atoi(str);
    sign = 1;
    if (res < 0  || *str == '-')
    {
        str++;
        sign = -1;
    }
    while (ft_isdigit(*str))
        str++;
    if (*str != '.')
        return (res);
    str++;
    return (get_decimal_point(res, str) * sign);
}


    int get_2darray_size(char **arr)
    {
        int i;

        i = 0;
        while (arr[i])
            i++;  
        return (i);    
    }

void parse_color(char *str, t_color *colors)
{
    char **rgb;
    double c[3];
    int     i;

    i = 0;
    rgb = ft_split(str, ',');
    if (get_2darray_size(rgb) != 3)
        errormsg("INVALID COLOR VALUES");    
    while (i < 3)
    {
        if(skip_dot_verify_digits(rgb[i]))
        {
            errormsg("INVALID COLOR VALUES");      
        }
        i++;
    }
    c[0] = parse_double(rgb[0]);
    c[1] = parse_double(rgb[1]);
    c[2] = parse_double(rgb[2]);
    if ((c[0] > 255 || c[0] < 0) ||
        (c[1] > 255 || c[1] < 0) ||
        (c[2] > 255 || c[2] < 0))
    {
            errormsg("INVALID COLOR VALUES");
    }
    free_memmory(rgb);
    colors->r = c[0];
    colors->g = c[1];
    colors->b =  c [2];
}

// static int		get_ambi_light(char *line, int check, int i, t_ambi *ambi)
// {
// 	double	light;

// 	while (line[i] != ' ' && line[i] != '\0')
// 	{
// 		if ((line[i] == '1' || line[i] == '0') && check == 0)
// 		{
// 			light = get_single_double(line, i);
// 			i = get_index(line, i);
// 			check++;
// 		}
// 		i++;
// 	}
// 	if (light > 1 || light < 0)
// 	{
// 		errormsg(6);
// 	}
// 	ambi->light = light;
// 	return (check);
// }

// static int		ambient_loop(char *line, int i, int check, t_ambi *ambi)
// {
// 	while (line[i] != '\0')
// 	{
// 		if (line[i] == ' ')
// 			i++;
// 		else if (line[i] >= '0' && line[i] <= '9')
// 		{
// 			if (check == 0)
// 			{
// 				check = get_ambi_light(line, check, i, ambi);
// 				i = get_index(line, i);
					
// 			}
// 			else if (check == 1)
// 			{
// 				check = get_ambi_rgb(line, check, i, ambi);
				
// 				i = get_index(line, i);
// 			}
// 		}
// 		else if (line[i] == '-')
// 		{
			
// 			errormsg(50);
// 		}
// 		else if ((!(line[i] >= '0' && line[i] <= '9')) || (!(line[i] == ' ')))
// 		{
// 			errormsg(5);
// 		}
// 	}
// 	return (check);
// }

int skip_dot_verify_digits(char *str)
{
    int i;
    int dot_count;
    
    i = 0;
    dot_count = 0;
    while (i < str[i])
    {
        if (str[i] == '.')
        {
            dot_count++;
            i++;
            continue;
        }
        if(!ft_isdigit(str[i]))
            return (1);
        i++;
    }
    if (ft_strlen(str) == 1 && *str == '.')
    {
        return (1);
    }
    if (dot_count > 1)
    {
        return (1);
    }
    return (0);        
}



int verify_digits(char **color_split ,char **info, t_rt *rt)
{
    int i;

    i = 0;
    while (i < 3)
    {
        if (skip_dot_verify_digits(color_split[i]))
            return (0);
        i++;
    }
    if (skip_dot_verify_digits(info[1]))
        return(0);  
    if (rt->ambi.light < 0 || rt->ambi.light > 1)
        return(0); 
    return(1);
}

void parse_ambient_lighting(char **info, t_rt *rt)
{
    char **color_split;

    color_split = ft_split(info[2], ',');
    rt->ambi.light = parse_double(info[1]);
    if (get_2darray_size(info) == 3 && 
        verify_digits(color_split, info, rt))
    {
        parse_color(info[2], &rt->ambi.color);
        // scene_data->amb_set = 1;
    }
    else
    {   
        free_2d_char_array(color_split);
        errormsg("Wrong Input");
    }
    free_2d_char_array(color_split);
}

void free_2d_char_array(char **arr)
{
    int i;
    i = 0;

    while (arr[i])
    {
        free_memmory(&arr[i]);
        i++;
    }
    free_memmory(arr);
}



// void			get_ambient(char *line, t_rt *rt)
// {
// 	// int		i;
// 	// int		check;
// 	// parse_ambient_lighting(char **info, t_rt *rt)

// 	// check = 0;
// 	// i = 1;
// 	// check = ambient_loop(line, i, check, &ambi);
// 	// if (check != 4)
// 	// 	errormsg(7);
// 	// rt->ambi = ambi;



// 	// rt->ambi = ambi;
// }
