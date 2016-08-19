/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simzam <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/19 11:01:39 by simzam            #+#    #+#             */
/*   Updated: 2016/08/19 12:01:03 by simzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

float		mix(float a, float b, float mix)
{
	return (b * mix + a * (1 - mix));
}

int 		ft_strlen(unsigned char *s)
{
	unsigned int 	i;
	i = 0;
	if (s)
	{
		while (s[i])
			i++;
	}
	return ((int)i);
}

t_vec3		trace(t_vec3 *ray_origin, t_vec3 *ray_dir, t_sphere **spheres, const int *depth)
{
	float			near;
	t_sphere		*sphere;
	int 			i;
	int 			obj_len;

	t_vec3			scolor;
	t_vec3 			phit;
	t_vec3			nhit;
	float			bias;
	t_bool			inside;
	float			facingratio;
	float 			fresneleffect;
	t_vec3			refldir;
	t_vec3			reflection;
	t_vec3			refraction;
	float			ior;
	float			eta;
	float			cosi;
	float			k;

	near = INFINITY;
	sphere = NULL;
	i = -1;
	obj_len = 1;
	while (++i < obj_len)
	{
		spheres[i]->roots[0] = INFINITY;
		spheres[i]->roots[1] = INFINITY;
		if (sp_itsc(v3_sub((*spheres)[i].center, *ray_origin), ray_dir, spheres[i]) == TRUE)
		{
			if ((*spheres)[i].roots[0] < 0)
				(*spheres)[i].roots[0] = (*spheres)[i].roots[1];
			if ((*spheres)[i].roots[0] < near)
			{
				near = (*spheres)[i].roots[0];
				sphere = spheres[i];
			}
		}
	}
	if (!sphere)
		return (vec3(255, 255, 255));
	phit = v3_add(*ray_origin, v3_muls(*ray_dir, near));
	nhit = v3_sub(phit, sphere->center);
	nhit = v3_norm(nhit);
	bias = 1e-4;
	inside = FALSE;
	if (v3_dot(*ray_dir, nhit) > 0)
	{
		nhit = v3_muls(nhit, -1.0);
		inside = TRUE;
	}
	if ((sphere->transparency > 0  || sphere->reflection > 0)
		&& *depth < MAX_RAY_DEPTH)
	{
		facingratio = -v3_dot(*ray_dir, nhit);
		//const float a = (float)pow(1 - facingratio, 3);
		fresneleffect = mix((float)pow(1 - facingratio, 3), 1.0, 0.1);
	//	Vec3f refldir = raydir - nhit * 2 * raydir.dot(nhit);
		refldir = v3_sub(*ray_dir, v3_muls(nhit, 2 * v3_dot(*ray_dir, nhit)));
		refldir = v3_norm(refldir);
		t_vec3 orig = v3_add(phit, v3_muls(nhit, bias));
		reflection = trace(&orig, &refldir, spheres, depth + 1);
	}
	if (sphere->transparency)
	{
		ior = 1.1;
		if (inside)
			eta = ior;
		else
			eta = 1 / ior;
		cosi = -v3_dot(nhit, *ray_dir);
		k = 1 - eta  * eta * (1  - cosi  * cosi);
		//Vec3f refrdir = raydir * eta + nhit * (eta * cosi - sqrt(k))
		t_vec3 refrdir = v3_add(v3_muls(*ray_dir, eta), v3_muls(nhit, eta * cosi - sqrt(k)));
		refrdir = v3_norm(refrdir);
	//	refraction = trace(phit - nhit * bias, refrdir, spheres, depth + 1);
		t_vec3 orig = v3_add(phit, v3_muls(nhit, bias));
		refraction = trace(&orig, &refrdir, spheres, depth + 1);
		float val =  v3_dot(v3_muls(reflection, fresneleffect), refraction) * (1 - fresneleffect) * sphere->transparency *
					sphere->reflection;
		scolor = vec3(val, val, val);
	}
	else
	{
		i = -1;
		while (++i < obj_len)
		{
			if ((*spheres)[i].ecolor.x > 0)
			{
				t_vec3 transmission = vec3(1, 1, 1);
				t_vec3 light_dir = v3_sub((*spheres)[i].center, phit);
				light_dir = v3_norm(light_dir);
				int 	j = -1;
				while (++j < obj_len)
				{
					if (i != j)
					{
						if (sp_itsc(v3_sub((*spheres)[j].center, v3_add(phit, v3_muls(nhit, bias))), &light_dir, sphere))
						{
							transmission = vec3(1, 1, 1);
							break;
						}
					}
				}
				float p1 = v3_dot(sphere->scolor, transmission) * max(0.0, v3_dot(nhit, light_dir));
				scolor = v3_add(scolor, v3_muls((*spheres)[i].ecolor, p1)); 
			}
		}
	}
	return (v3_add(scolor, sphere->ecolor));
}

float	min(float i, float j)
{
	if (i <= j)
		return (i);
	return (j);
}

float	max(float i, float j)
{
	if (i <= j)
		return (j);
	return (i);
}
	/* Output data as PPM file */
void saveppm(char *filename, char *img, int width, int height){
	/* FILE pointer */
	FILE *f;

	/* Open file for writing */
	f = fopen(filename, "w");

	/* PPM header info, including the size of the image */
	fprintf(f, "P6 %d %d %d\n", width, height, 255);

	/* Write the image data to the file - remember 3 byte per pixel */
	fwrite(img, 3, width*height, f);

	/* Make sure you close the file */
	printf("Done writing\n");
	fclose(f);
}

void		render(t_sphere **spheres)
{
	int width = 640, height = 480;
	t_vec3	*image;
	t_vec3	*pixel;

	if (!(image = (t_vec3 *)malloc(width * height * sizeof(t_vec3))))
		return ;
	pixel = image;
	float fov = 30;
	float ar = width / (float)height;
	float angle = tan(M_PI * 0.5 * fov / 180);
	int x = -1, y = -1;
	int pos;

	void	*mlx_ptr;
	void	*win_ptr;
	void	*img;
	char	*img_ptr;
	int 	bpp;
	int 	sl;
	int 	endian;

	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, width, height, "Ray Tracer");
	img = mlx_new_image(mlx_ptr, width, height);
	img_ptr = mlx_get_data_addr(mlx_ptr, &bpp, &sl, &endian);

	//Trace Rays
	while (pixel && ++y < height)
	{
		float xx = (2 * ((x + 0.5) * (1 /(float)width)) - 1) * angle * ar;
		float yy = (1 - 2 * ((y + 0.5) * (1 / (float)height)) - 1) * angle;
		t_vec3 raydir = vec3(xx, yy, -1);
		raydir = v3_norm(raydir);
		t_vec3 new_ray = vec3(2, 3, 5);
		if (pixel)
			*pixel = trace(&new_ray, &raydir, spheres, 0);
		pixel++;
	}
	int i = -1;
	y = -1;
	while (++y < height)
	{
		x = -1;
		if (i < 640)
		{
		while (++x < width)
		{
			pos = x *  4 + y * sl;
			if (endian == 0)
			{
				img_ptr[pos] = (char)min(1.0, (image[++i]).x) * 255;
				img_ptr[pos + 1] = (char)min(1.0, (image[i]).y) * 255;
				img_ptr[pos + 2] = (char)min(1.0, (image[i]).z) * 255;
				/*	img_ptr[pos] = (char)min(1.0, (*pixel).x) >> (i << 3) & 255;
					img_ptr[pos + 1] = (char)min(1.0, (*pixel).y) >> (i << 3) & 255;
					img_ptr[pos + 2] = (char)min(1.0, (*pixel).z) >> (i << 3) & 255;*/
			}
			else
			{
				img_ptr[pos] = (char)min(1.0, (image[++i]).z) * 255;
				img_ptr[pos + 1] = (char)min(1.0, (image[i]).y) * 255;
				img_ptr[pos + 2] = (char)min(1.0, (image[i]).x) * 255;
					/*img_ptr[pos] = (char)min(1.0, (*pixel).x) >> (bpp - ((i + 1) << 3)) & 255;
					img_ptr[pos + 1] = (char)min(1.0, (*pixel).y) >> (bpp - ((i + 1) << 3)) & 255;
			 		img_ptr[pos + 2] = (char)min(1.0, (*pixel).z) >> (bpp - ((i + 1) << 3)) & 255;*/
			}
		}}
	}
	printf("In Render...After tracing rays\n");
	saveppm("image.ppm", img_ptr, width, height);
	mlx_put_image_to_window(mlx_ptr, win_ptr, img, 0, 0);
	mlx_loop(mlx_ptr);
	free(image);
}

t_sphere	new_sphere(t_vec3 pos, float radius, t_vec3 scolor, int refl, int trans)
{
	t_sphere sphere;
	t_sphere *sp;

	sp = &sphere;
	sp->center = pos;
	sp->radius = radius;
	sp->radius2 = radius * radius;
	sp->scolor = scolor;
	sp->reflection = refl;
	sp->transparency = trans;
	return (*sp);
}

int main(void)
{
	t_sphere spheres[2];
	t_sphere *sp;

	spheres[0] = new_sphere(vec3(0.0, -10004, -20), 10000, vec3(0.20, 0.20, 0.20), 0, 0);
	spheres[1] = new_sphere(vec3(0.0, 20, -30), 3, vec3(0.0, 0.0, .0), 0, 0);
	spheres[1].ecolor = vec3(3, 3, 3);
	sp = spheres;
	render(&sp);
	return 0;
}
