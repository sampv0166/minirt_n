/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcouto <lcouto@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 21:04:41 by lcouto            #+#    #+#             */
/*   Updated: 2020/11/14 15:04:41 by lcouto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

# include "minirt.h"

/*
** Holds values for RGB colors.
*/

typedef struct			s_color
{
	int					r;
	int					g;
	int					b;
}						t_color;

typedef struct			s_tuple
{
	double				x;
	double				y;
	double				z;
	int					w;
}						t_tuple;

typedef struct			s_rgba
{
	double				r;
	double				b;
	double				g;
	double				a;
}						t_rgba;

typedef struct			s_matrix
{
	double				**matrix;
	size_t				row;
	size_t				col;
}						t_matrix;


/*
** Vector operations.
*/

int						double_equal(double a, double b);
t_tuple					create_tuple(double x, double y, double z, int w);
t_tuple					add_tuple(t_tuple t1, t_tuple t2);
t_tuple					subtract_tuple(t_tuple t1, t_tuple t2);
t_tuple					negate_tuple(t_tuple t1);
t_tuple					scalar_x_tuple(t_tuple t1, double times);
double					vector_magnitude(t_tuple t1);
t_tuple					normalize_v(t_tuple t1);
double					dot_product(t_tuple t1, t_tuple t2);
t_tuple					cross_product(t_tuple t1, t_tuple t2);

/*
** Color operations.
*/

t_rgba					add_color(t_rgba c1, t_rgba c2);
t_rgba					scalar_color(t_rgba color, double scalar);
t_rgba					mult_color(t_rgba c1, t_rgba c2);
t_rgba					normalize_color(int r, int g, int b);
t_color					denorm_color(t_rgba norm);
t_rgba					tuple_to_rgba(t_tuple tuple);
t_rgba					create_rgba(double r, double g, double b, double a);
t_tuple					rgba_to_tuple(t_rgba rgba);

/*
** Matrix operations.
*/

t_matrix				create_matrix(int row, int col);
void					free_matrix(t_matrix matrix);
t_matrix				mult_matrix(t_matrix m1, t_matrix m2);
t_tuple					mult_matrix_tuple(t_matrix m1, t_tuple t1);
t_matrix				transpose_matrix(t_matrix src);
double					cofactor_4x4(t_matrix mat, int row, int col);
double					det_4x4(t_matrix mat);
t_matrix				invert_matrix(t_matrix mat);
t_matrix				translation(double x, double y, double z);
t_matrix				scaling(double x, double y, double z);

#endif
