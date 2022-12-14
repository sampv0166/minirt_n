/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canvas.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcouto <lcouto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 21:11:41 by lcouto            #+#    #+#             */
/*   Updated: 2021/02/13 19:08:50 by lcouto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

void				cast_pixel(t_raycaster *rc, t_rt *rt,
t_mlx *mlx, t_cam *cam)
{
	t_color		color;
	t_rgba		lt_output;
	t_comps		comps;
	int			coord[2];

	coord[0] = rc->x;
	coord[1] = rc->y;
	if (rc->hit)
	{
		prepare_computations(&comps, rt, rc);
		lt_output = shade_hit(comps, rt);
		normalize_pixel_color(&lt_output);
		color = denorm_color(lt_output);
		if (rc->y <= (double)HEIGHT && rc->x <= (double)WIDTH
		&& rc->x >= 0 && rc->y >= 0)
			ft_pixelput(cam, coord, mlx,
			create_trgb(0, color.r, color.g, color.b));
	}
	else
		ft_pixelput(cam, coord, mlx, create_trgb(0, 0, 0, 0));
}

void				raycaster(t_rt *rt, t_mlx *mlx, t_cam *cam)
{
	t_raycaster	rc;

	rc.y = 0;
	while (rc.y < HEIGHT)
	{
		rc.x = 0;
		while (rc.x < WIDTH)
		{
			rc.intersec_list = (t_intersec *)ec_malloc(sizeof(t_intersec));
			rc.intersec_list = init_intersec_list(rc.intersec_list);
			rc.ray = ray_for_pixel(cam, rc.x, rc.y);
			intersect_all_polys(rt, &rc);
			rc.hit = intersec_hit(rc.intersec_list);
			cast_pixel(&rc, rt, mlx, cam);
			free_intersecs(rc.intersec_list);
			rc.x = rc.x + 1;
		}
		rc.y = rc.y + 1;
	}
}

void				render(t_rt *rt, t_mlx *mlx)
{
	
	create_image(rt, mlx);
	mlx->win = mlx_new_window(mlx->mlx, WIDTH,HEIGHT, "MiniRT");
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->cam->img, 0, 0);
}
