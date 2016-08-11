/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simzam <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/11 06:41:29 by simzam            #+#    #+#             */
/*   Updated: 2016/08/11 06:41:32 by simzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/matlib.h"

inline t_vec3	vec3(float x, float y, float z)
{
	return ((t_vec3){x, y, z});
}

inline t_vec3	v3_add(t_vec3 a, t_vec3 b)
{
	return ((t_vec3){a.x + b.x, a.y + b.y, a.z + b.z});
}

inline t_vec3	v3_adds(t_vec3 a, float s)
{
	return ((t_vec3){a.x + s,   a.y + s,   a.z + s});
}
inline t_vec3	v3_sub(t_vec3 a, t_vec3 b)
{
	return ((t_vec3){a.x - b.x, a.y - b.y, a.z - b.z});
}

inline t_vec3	v3_subs(t_vec3 a, float s)
{
	return ((t_vec3){a.x - s,   a.y - s,   a.z - s});
}
