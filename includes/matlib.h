/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matlib.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simzam <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/11 06:29:44 by simzam            #+#    #+#             */
/*   Updated: 2016/08/11 06:30:28 by simzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATLIB_H
#define MATLIB_H
#include <math.h>
#include <stdio.h>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

typedef struct 	s_vec3
{
	float x;
	float y;
	float z;
}				t_vec3;

typedef union	u_mat44{
	float m[4][4];
	struct
	{
		float m00;
		float m01;
		float m02;
		float m03;
		float m10;
		float m11;
		float m12;
		float m13;
		float m20;
		float m21;
		float m22;
		float m23;
		float m30;
		float m31;
		float m32;
		float m33;
	};
}				t_mat4;

inline t_vec3	vec3(float x, float y, float z);
inline t_vec3	v3_add(t_vec3 a, t_vec3 b);
inline t_vec3	v3_adds(t_vec3 a, float s);
inline t_vec3	v3_sub(t_vec3 a, t_vec3 b);
inline t_vec3	v3_subs(t_vec3 a, float s);
inline t_vec3	v3_norm(t_vec3 v);
inline t_vec3	v3_proj(t_vec3 v, t_vec3 onto);
inline t_vec3	v3_cross(t_vec3 a, t_vec3 b);
inline t_vec3	v3_mul(t_vec3 a, t_vec3 b);
inline t_vec3	v3_muls(t_vec3 a, float s);
inline t_vec3	v3_div(t_vec3 a, t_vec3 b);
inline t_vec3	v3_divs(t_vec3 a, float s);
inline float	v3_angle_between(t_vec3 a, t_vec3 b);
inline float 	v3_dot(t_vec3 a, t_vec3 b);
inline float 	v3_length(t_vec3 v);

inline t_mat4 mat4(
	float m00, float m10, float m20, float m30,
	float m01, float m11, float m21, float m31,
	float m02, float m12, float m22, float m32,
	float m03, float m13, float m23, float m33
);

inline t_mat4	m4_identity();
inline t_mat4	m4_translation(t_vec3 offset);
inline t_mat4	m4_scaling(t_vec3 scale);
inline t_mat4	m4_rotation_x(float angle_in_rad);
inline t_mat4	m4_rotation_y(float angle_in_rad);
inline t_mat4	m4_rotation_z(float angle_in_rad);
t_mat4			m4_rotation(float angle_in_rad, t_vec3 axis);
t_mat4			m4_ortho(float left, float right, float bottom,
						float top,
						float back,
						float front);
t_mat4			m4_perspective(float vertical_field_of_view_in_deg,
							float aspect_ratio,
							float near_view_distance,
							float far_view_distance);
t_mat4			m4_look_at(t_vec3 from, t_vec3 to, t_vec3 up);
inline t_mat4	m4_transpose(t_mat4 matrix);
inline t_mat4	m4_mul(t_mat4 a, t_mat4 b);
t_mat4			m4_invert_affine(t_mat4 matrix);
t_vec3			m4_mul_pos(t_mat4 matrix, t_vec3 position);
t_vec3			m4_mul_dir(t_mat4 matrix, t_vec3 direction);
void 			m4_print(t_mat4 matrix);
void			m4_printp(t_mat4 matrix, int width, int precision);
void			m4_fprint(FILE* stream, t_mat4 matrix);
void 			m4_fprintp(FILE* stream, t_mat4 matrix,
						   int width, int precision);

#endif /* MATLIB_H */