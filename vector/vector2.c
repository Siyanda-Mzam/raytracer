/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simzam <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/11 06:45:16 by simzam            #+#    #+#             */
/*   Updated: 2016/08/11 06:45:18 by simzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/matlib.h"

inline t_vec3	v3_mul(t_vec3 a, t_vec3 b)
{
	return ((t_vec3){a.x * b.x, a.y * b.y, a.z * b.z});
}

inline t_vec3	v3_muls(t_vec3 a, float s)
{
	return ((t_vec3){a.x * s,   a.y * s,   a.z * s});
}

inline t_vec3	v3_div(t_vec3 a, t_vec3 b)
{
	return (t_vec3){ a.x / b.x, a.y / b.y, a.z / b.z };
}

inline t_vec3	v3_divs(t_vec3 a, float s)
{
	return ((t_vec3){a.x / s,   a.y / s,   a.z / s});
}

inline float 	v3_length(t_vec3 v)
{
	return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
}