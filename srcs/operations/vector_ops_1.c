/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_ops_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcouto <lcouto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 16:52:52 by lcouto            #+#    #+#             */
/*   Updated: 2021/02/13 17:29:40 by lcouto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

t_tuple	create_tuple(double x, double y, double z, int w)
{
	t_tuple	tuple;

	tuple.x = x;
	tuple.y = y;
	tuple.z = z;
	tuple.w = w;
	return (tuple);
}

t_tuple	add_tuple(t_tuple t1, t_tuple t2)
{
	t_tuple	new;

	// ft_putnbr_fd(t1.w, 2);
	// ft_putnbr_fd(t2.w, 2);

	if ((t1.w != 1 && t1.w != 0) || (t2.w != 1 && t2.w != 0))
		errormsg("W parameter of a tuple can be only 1 for a point or 0 for a vector.");
	new.x = t1.x + t2.x;
	new.y = t1.y + t2.y;
	new.z = t1.z + t2.z;
	new.w = t1.w + t2.w;
	if (new.w != 1 && new.w != 0)
		errormsg("W parameter of a tuple can be only 1 for a point or 0 for a vector. You cannot add two points.");
	return (new);
}

t_tuple	subtract_tuple(t_tuple t1, t_tuple t2)
{
	t_tuple	new;

	if ((t1.w != 1 && t1.w != 0) || (t2.w != 1 && t2.w != 0))
		errormsg("W parameter of a tuple can be only 1 for a point or 0 for a vector.");
	new.x = t1.x - t2.x;
	new.y = t1.y - t2.y;
	new.z = t1.z - t2.z;
	new.w = t1.w - t2.w;
	if (new.w != 1 && new.w != 0)
		errormsg("W parameter of a tuple can be only 1 for a point or 0 for a vector. You cannot subtract a point from a vector.");
	return (new);
}

t_tuple	negate_tuple(t_tuple t1)
{
	t_tuple	new;

	if (t1.w != 1 && t1.w != 0)
		errormsg("W parameter of a tuple can be only 1 for a point or 0 for a vector.");
	new.x = t1.x * -1;
	new.y = t1.y * -1;
	new.z = t1.z * -1;
	new.w = t1.w * -1;
	if (new.w != 1 && new.w != 0 && new.w != -1)
		errormsg("W parameter of a tuple can be only 1 for a point or 0 for a vector. You cannot add two points.");
	return (new);
}

t_tuple	scalar_x_tuple(t_tuple t1, double times)
{
	t_tuple	new;

	if (t1.w != 1 && t1.w != 0)
		errormsg("W parameter of a tuple can be only 1 for a point or 0 for a vector.");
	new.x = t1.x * times;
	new.y = t1.y * times;
	new.z = t1.z * times;
	new.w = t1.w * times;
	return (new);
}
