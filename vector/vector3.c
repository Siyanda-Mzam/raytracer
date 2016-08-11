/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simzam <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/11 06:47:22 by simzam            #+#    #+#             */
/*   Updated: 2016/08/11 06:47:24 by simzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/matlib.h"

inline float 	v3_dot(t_vec3 a, t_vec3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

inline t_vec3	v3_norm(t_vec3 v)
{
	float len;

	len = v3_length(v);
	if (len > 0)
		return (t_vec3){ v.x / len, v.y / len, v.z / len };
	else
		return (t_vec3){ 0, 0, 0};
}

inline t_vec3	v3_proj(t_vec3 v, t_vec3 onto)
{
	return v3_muls(onto, v3_dot(v, onto) / v3_dot(onto, onto));
}

inline t_vec3	v3_cross(t_vec3 a, t_vec3 b)
{
	return ((t_vec3)
			{
				a.y * b.z - a.z * b.y,
				a.z * b.x - a.x * b.z,
				a.x * b.y - a.y * b.x
			});
}

inline float 	v3_angle_between(t_vec3 a, t_vec3 b)
{
	return (acosf( v3_dot(a, b) / (v3_length(a) * v3_length(b))));
}
