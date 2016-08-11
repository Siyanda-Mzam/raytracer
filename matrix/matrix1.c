/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simzam <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/11 06:55:38 by simzam            #+#    #+#             */
/*   Updated: 2016/08/11 06:55:40 by simzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/matlib.h"

inline t_mat4		mat4(
					 float m00, float m10, float m20, float m30,
					 float m01, float m11, float m21, float m31,
					 float m02, float m12, float m22, float m32,
					 float m03, float m13, float m23, float m33
					 )
{
	return ((t_mat4)
			{
				.m[0][0] = m00, .m[1][0] = m10, .m[2][0] = m20, .m[3][0] = m30,
				.m[0][1] = m01, .m[1][1] = m11, .m[2][1] = m21, .m[3][1] = m31,
				.m[0][2] = m02, .m[1][2] = m12, .m[2][2] = m22, .m[3][2] = m32,
				.m[0][3] = m03, .m[1][3] = m13, .m[2][3] = m23, .m[3][3] = m33
			});
}

inline t_mat4		m4_identity()
{
	return (mat4(
				 1,  0,  0,  0,
				 0,  1,  0,  0,
				 0,  0,  1,  0,
				 0,  0,  0,  1
				 ));
}

inline t_mat4		m4_translation(t_vec3 offset)
{
	return (mat4(
				 1,  0,  0,  offset.x,
				 0,  1,  0,  offset.y,
				 0,  0,  1,  offset.z,
				 0,  0,  0,  1
				 ));
}

inline t_mat4		m4_scaling(t_vec3 scale)
{
	float	x;
	float	y;
	float	z;

	x = scale.x;
	y = scale.y;
	z = scale.z;
	return (mat4(
				 x, 0, 0, 0,
				 0, y, 0, 0,
				 0,  0, z, 0,
				 0, 0, 0, 1
				 ));
}