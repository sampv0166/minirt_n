/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcouto <lcouto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 16:18:07 by lcouto            #+#    #+#             */
/*   Updated: 2021/02/15 14:13:04 by lcouto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

void		create_image(t_rt *rt, t_mlx *mlx)
{
	// t_cam		*current_cam;

	// current_cam = rt->cam;
	// while (current_cam)
	// {
		
		camera_pixel_size(rt->cam);
		rt->cam->img = mlx_new_image(mlx->mlx, WIDTH,
		HEIGHT);
		rt->cam->address = mlx_get_data_addr(rt->cam->img, &mlx->bpp,
			&mlx->line_leng, &mlx->endian);
		if (rt->qts.cam > 0)
			raycaster(rt, mlx, rt->cam);
	
		// rt->qts.cam = rt->qts.cam - 1;
		// current_cam = current_cam->next;
		// 	exit(0);
		// }

	mlx->cam = rt->cam;
	mlx->begin = mlx->cam;
}

void		add_ambient_to_lights(t_rt *rt)
{
	t_light *current_lt;

	current_lt = rt->light;
	while (current_lt)
	{
		write(1, "2323", 5);
		current_lt->intensity = add_color(current_lt->intensity,
			(scalar_color(normalize_color(rt->ambi.color.r,
			rt->ambi.color.g, rt->ambi.color.b),
			rt->ambi.light)));
		current_lt = current_lt->next;
	}
}
