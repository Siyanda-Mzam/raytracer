/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simzam <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/11 07:16:47 by simzam            #+#    #+#             */
/*   Updated: 2016/08/11 07:16:48 by simzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/matlib.h"

t_vec3	m4_mul_pos(t_mat4 matrix, t_vec3 position)
{
	float 	w;
	t_vec3	result;

	result = vec3(
				  matrix.m00 * position.x + matrix.m10 *
				  position.y + matrix.m20 * position.z + matrix.m30,
				  matrix.m01 * position.x + matrix.m11 *
				  position.y + matrix.m21 * position.z + matrix.m31,
				  matrix.m02 * position.x + matrix.m12 *
				  position.y + matrix.m22 * position.z + matrix.m32
				  );
	w = matrix.m03 * position.x + matrix.m13 *
	position.y + matrix.m23 * position.z + matrix.m33;
	if (w != 0 && w != 1)
		return (vec3(result.x / w, result.y / w, result.z / w));
	return (result);
}

t_vec3	m4_mul_dir(t_mat4 matrix, t_vec3 direction)
{
	t_vec3	result;
	float 	w;

	result = vec3(
				  matrix.m00 * direction.x + matrix.m10 *
				  direction.y + matrix.m20 * direction.z,
				  matrix.m01 * direction.x + matrix.m11 *
				  direction.y + matrix.m21 * direction.z,
				  matrix.m02 * direction.x + matrix.m12 *
				  direction.y + matrix.m22 * direction.z
				  );
	w = matrix.m03 * direction.x + matrix.m13 *
	direction.y + matrix.m23 * direction.z;
	if (w != 0 && w != 1)
		return (vec3(result.x / w, result.y / w, result.z / w));
	
	return (result);
}