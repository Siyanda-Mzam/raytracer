/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simzam <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/11 07:00:20 by simzam            #+#    #+#             */
/*   Updated: 2016/08/11 07:00:23 by simzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/matlib.h"

inline t_mat4		m4_rotation_x(float angle_in_rad)
{
	float	s;
	float	c;

	s = sinf(angle_in_rad);
	c = cosf(angle_in_rad);
	return (mat4(
				 1,  0,  0,  0,
				 0,  c, -s,  0,
				 0,  s,  c,  0,
				 0,  0,  0,  1
				 ));
}

inline t_mat4		m4_rotation_y(float angle_in_rad)
{
	float	s;
	float	c;

	s = sinf(angle_in_rad);
	c = cosf(angle_in_rad);
	return (mat4(
				 c,  0,  s,  0,
				 0,  1,  0,  0,
				 -s,  0,  c,  0,
				 0,  0,  0,  1
				 ));
}

inline t_mat4		m4_rotation_z(float angle_in_rad)
{
	float	s;
	float	c;

	s = sinf(angle_in_rad);
	c = cosf(angle_in_rad);
	return (mat4(
				 c, -s,  0,  0,
				 s,  c,  0,  0,
				 0,  0,  1,  0,
				 0,  0,  0,  1
				 ));
}

inline t_mat4		m4_transpose(t_mat4 matrix)
{
	return (mat4(
				 matrix.m00, matrix.m01, matrix.m02, matrix.m03,
				 matrix.m10, matrix.m11, matrix.m12, matrix.m13,
				 matrix.m20, matrix.m21, matrix.m22, matrix.m23,
				 matrix.m30, matrix.m31, matrix.m32, matrix.m33
				 ));
}

inline t_mat4		m4_mul(t_mat4 a, t_mat4 b)
{
	t_mat4 result;
	int 	i;
	int 	j;
	int 	k;

	i = -1;
	while(++i < 4)
	{
		j = -1;
		while(++j < 4)
		{
			float sum = 0;
			k = -1;
			while(++k < 4) {
				sum += a.m[k][j] * b.m[i][k];
			}
			result.m[i][j] = sum;
		}
	}
	return (result);
}