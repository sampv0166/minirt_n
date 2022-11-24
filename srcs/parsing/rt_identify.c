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


static void	rt_id_polys(char *line, t_rt *rt)
{
	if (ft_strncmp(line, "sp ", 3) == 0)
	{
		get_sphere(line, rt);
	
	}
	else if (ft_strncmp(line, "pl ", 3) == 0)
		get_plane(line, rt);
	else if (ft_strncmp(line, "cy ", 3) == 0)
		get_cylinder(line, rt);
}

static int	valid_poly(char *line)
{
	if (ft_strncmp(line, "sp ", 3) == 0 || ft_strncmp(line, "pl ", 3) == 0 ||
	ft_strncmp(line, "sq ", 3) == 0 || ft_strncmp(line, "cy ", 3) == 0 ||
	ft_strncmp(line, "tr ", 3) == 0 || ft_strncmp(line, "bn ", 3) == 0)
		return (1);
	else
		return (0);
}

void		rt_identify(char *line, t_rt *rt, t_mlx *mlx)
{
	if (line[0] == 'R' && line[1] == ' ')
	{
		// rt->qts.reso = rt->qts.reso + 1;
		// if (rt->qts.reso > 1)
		// 	errormsg(9);
		get_resolution(line, rt, mlx);
	}
	else if (line[0] == 'A' && line[1] == ' ')
	{
		// rt->qts.ambi = rt->qts.ambi + 1;
		// if (rt->qts.ambi > 1)
		// 	errormsg(10);
		get_ambient(line, rt);
			
	}
	else if (line[0] == 'C' && line[1] == ' ')
	{
		get_camera(line, rt);
// 
	}
	else if (line[0] == 'L' && line[1] == ' ')
	{
		get_light(line, rt);
		
	}
	else if (valid_poly(line) == 1)
		rt_id_polys(line, rt);
	else if (line[0] == '\n' || line[0] == '\0')
		return ;
	else
		errormsg(2);
}
