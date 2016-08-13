/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simzam <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/11 07:02:05 by simzam            #+#    #+#             */
/*   Updated: 2016/08/11 07:16:12 by simzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/matlib.h"

t_mat4		m4_rotation(float angle_in_rad, t_vec3 axis)
{
	t_vec3	normalized_axis;
	t_vec3	xyz;
	float 	c;
	float 	s;

	normalized_axis = v3_norm(axis);
	xyz.x = normalized_axis.x;
	xyz.y = normalized_axis.y;
	xyz.z = normalized_axis.z;
	c = cosf(angle_in_rad);
	s = sinf(angle_in_rad);
	return (mat4(
	c + xyz.x * xyz.x * (1 - c), xyz.x * xyz.y * (1 - c) - xyz.z * s, xyz.x * xyz.z * (1 - c) + xyz.y * s, 0,
	xyz.y * xyz.x * (1 - c) + xyz.z * s,  c + xyz.y * xyz.y * (1 - c), xyz.y * xyz.z * (1 - c) - xyz.x * s, 0,
	xyz.z* xyz.x * (1 - c) - xyz.y * s, xyz.z * xyz.y * (1 - c) + xyz.x * s,  c + xyz.z * xyz.z * (1 - c), 0,
	0, 0, 0, 1
	));
}

t_mat4		m4_ortho(float left, float right, float bottom, float top, float back, float front)
{
	//float l = left, r = right, b = bottom, t = top, n = front, f = back;
	float tx = -(right + left) / (right - left);
	float ty = -(top + bottom) / (top - bottom);
	float tz = -(back + front) / (back - front);

	return (mat4(
				 2 / (right - left), 0, 0, tx,
				 0, 2 / (top - bottom), 0, ty,
				 0, 0, 2 / (back - front), tz,
				 0, 0, 0, 1
				 ));
}

t_mat4		m4_perspective(float vertical_field_of_view_in_deg,
							float aspect_ratio,
							float near_view_distance,
							float far_view_distance)
{
	float fovy_in_rad;
	float ar;
	float nd;
	float f;

	fovy_in_rad = vertical_field_of_view_in_deg / 180 * M_PI;
	f = 1.0f / tanf(fovy_in_rad / 2.0f);
	ar = aspect_ratio;
	nd = near_view_distance;
	float fd = far_view_distance;
	return (mat4(
				 f / ar, 0, 0, 0,
				 0, f, 0, 0,
				 0, 0, (fd + nd) / (nd - fd), (2 * fd * nd) / (nd - fd),
				 0, 0, -1, 0
				 ));
}

t_mat4		m4_look_at(t_vec3 from, t_vec3 to, t_vec3 up)
{
	t_vec3	x;
	t_vec3	y;
	t_vec3	z;

	z = v3_muls(v3_norm(v3_sub(to, from)), -1);
	x = v3_norm(v3_cross(up, z));
	y = v3_cross(z, x);
	return (mat4(
				 x.x, x.y, x.z, -v3_dot(from, x),
				 y.x, y.y, y.z, -v3_dot(from, y),
				 z.x, z.y, z.z, -v3_dot(from, z),
				 0,   0,   0,    1
				 ));
}

/*t_mat4		m4_invert_affine(t_mat4 matrix)
{
	// Create shorthands to access matrix members
	float m00 = matrix.m00,  m10 = matrix.m10,  m20 = matrix.m20,  m30 = matrix.m30;
	 float m01 = matrix.m01,  m11 = matrix.m11,  m21 = matrix.m21,  m31 = matrix.m31;
	 float m02 = matrix.m02,  m12 = matrix.m12,  m22 = matrix.m22,  m32 = matrix.m32;

	float 	c00;
	float 	c10;
	float 	c20;
	float 	c01;
	float 	c11;
	float 	c21;
	float 	c02;
	float 	c12;
	float 	c22;
	float 	det;

	// Invert 3x3 part of the 4x4 matrix that contains the rotation, etc.
	// That part is called R from here on.

	// Calculate cofactor matrix of R
	c00 = matrix.m11 * matrix.m22 - matrix.m12 * matrix.m21,
	c10 = -(matrix.m01 * matrix.m22 - matrix.m02 * matrix.m21),
	c20 = matrix.m01 * matrix.m12 - matrix.m02 * matrix.m11;
	c01 = -(matrix.m10 * matrix.m22 - matrix.m12 * matrix.m20),
	c11 = matrix.m00 * matrix.m22 - matrix.m02 * matrix.m20,
	c21 = -(matrix.m00 * matrix.m12 - matrix.m02 * matrix.m10);
	c02 = matrix.m10 * matrix.m21 - matrix.m11 * matrix.m20,
	c12 = -(matrix.m00 * matrix.m21 - matrix.m01 * matrix.m20),
	c22 = matrix.m00 * matrix.m11 - matrix.m01 * matrix.m10;

	// Caclculate the determinant by using the already calculated determinants
	// in the cofactor matrix.
	// Second sign is already minus from the cofactor matrix.
	det = m00 * c00 + m10 * c10 + m20 * c20;
	if (fabsf(det) < 0.00001)
		return (m4_identity());

	// Calcuate inverse of R by dividing the transposed cofactor matrix by the
	// determinant.
	float i00 = c00 / det,  i10 = c01 / det,  i20 = c02 / det;
	float i01 = c10 / det,  i11 = c11 / det,  i21 = c12 / det;
	float i02 = c20 / det,  i12 = c21 / det,  i22 = c22 / det;

	// Combine the inverted R with the inverted translation
	return (mat4(
				 i00, i10, i20,  -(i00*m30 + i10*m31 + i20*m32),
				 i01, i11, i21,  -(i01*m30 + i11*m31 + i21*m32),
				 i02, i12, i22,  -(i02*m30 + i12*m31 + i22*m32),
				 0,   0,   0,      1
				 ));
}*/