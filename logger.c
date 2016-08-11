/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simzam <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/11 07:20:53 by simzam            #+#    #+#             */
/*   Updated: 2016/08/11 07:20:55 by simzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/matlib.h"

void 					m4_print(t_mat4 matrix)
{
	m4_fprintp(stdout, matrix, 6, 2);
}

void m4_printp(t_mat4 matrix, int width, int precision)
{
	m4_fprintp(stdout, matrix, width, precision);
}

void m4_fprint(FILE* stream, t_mat4 matrix)
{
	m4_fprintp(stream, matrix, 6, 2);
}

void m4_fprintp(FILE* stream, t_mat4 matrix, int width, int precision)
{
	t_mat4		m;
	int 		w;
	int 		r;

	m = matrix;
	r = -1;
	w = width, p = precision;
	while (++r < 4)
	{
		fprintf(stream, "| %*.*f %*.*f %*.*f %*.*f |\n",
				w, p, m.m[0][r], w, p, m.m[1][r], w, p, m.m[2][r],
				w, p, m.m[3][r]
				);
	}
}
