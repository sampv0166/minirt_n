/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_identify.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcouto <lcouto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/06 22:01:19 by lcouto            #+#    #+#             */
/*   Updated: 2021/02/15 00:24:21 by lcouto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"



void check_for_a_c_l(char **line_split, t_rt *rt)
{
    if (line_split[0][0] == 'A')
    {
        if (rt->qts.ambi == 0)
        {
            parse_ambient_lighting(line_split, rt);
            rt->qts.ambi += 1;
        }
        else
        {
            errormsg("two ambient lights not allowed");
        }
    }
    else if (line_split[0][0] == 'C')
    {
        if (rt->qts.cam == 0)
        {
        parse_camera(line_split,rt);
            rt->qts.cam += 1;
        }
        else
        {
            errormsg("2 camera not allowed");
        }
    
    }
    else if (line_split[0][0] == 'L')
    {
        if (rt->qts.lt == 0)
        {
        parse_light(line_split,rt);
        rt->qts.lt +=1;
        }
        else
        {
            errormsg("two lights not allowed");
        }
    }
}

void replace_tabs_and_newline(char *line)
{
    int i;

    i = 0;
    while (line[i])
    {
        if (line[i] == '\t')
            line[i] = ' ';
        if (line[i] == '\n')
            line[i] = '\0';    
        i++;    
    }
}

void check_for_sp_pl_cy( char **info_split, t_rt *rt)
{
    if(info_split[0][0] == 's' && info_split[0][1] == 'p')
    {
        parse_sphere(info_split, rt);
        rt->qts.sp+=1;
    }
    else if (info_split[0][0] == 'p' && info_split[0][1] == 'l')
    {
        parse_plane(info_split, rt);
        rt->qts.pl+=1;
    }
    else if (info_split[0][0] == 'c' && info_split[0][1] == 'y')
    {
        parse_cylinder(info_split, rt);
        rt->qts.cy+=1;  
    }
}

void		parse_current_line(char *line, t_rt *rt)
{
	char **line_split;

    line_split = NULL;
	replace_tabs_and_newline(line);
    line_split = ft_split(line, ' ');
	
	if (line_split && ft_strlen(line_split[0]) == 1)
    {
     check_for_a_c_l(line_split, rt);
    }
    else if (line_split &&  ft_strlen(line_split[0]) == 2)
    {
        check_for_sp_pl_cy(line_split, rt);
    }
	else
	{
		errormsg2(2);
	}



}
