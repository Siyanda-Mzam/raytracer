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
	if (s)
	{
		i = 0;
		while (s[i])
			i++;
	}
	return (i);
}

/*static int 	len(t_sphere *spheres)
{
	unsigned int i;

	if (spheres)
	{
		i = 0;
		while ((spheres + i) != NULL)
			i++;
		return (i);
	}
	return (0);
}*/

t_vec3		trace(t_vec3 *ray_origin, t_vec3 *ray_dir, t_sphere **spheres, const int *depth)
{
	static float			near;
	static t_sphere		*sphere;
	static int 			i;
	static int 			obj_len;

	static t_vec3			scolor;
	static t_vec3 			phit;
	static t_vec3			nhit;
	static float			bias;
	static t_bool			inside;
	static float			facingratio;
	static float 			fresneleffect;
	static t_vec3			refldir;
	static t_vec3			reflection;
	static t_vec3			refraction;
	static float			ior;
	static float			eta;
	static float			cosi;
	static float			k;

	near = INFINITY;
	sphere = NULL;
	i = -1;
	obj_len = 1;//len(*spheres);
	while (++i < obj_len)
	{
		if (sp_itsc(v3_sub((*spheres)[i].center, *ray_origin), ray_dir, spheres[i]) == TRUE)
		{
		//	printf("Found an Intersection\n");
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
	scolor = vec3(0.0, 0.0, 0.0);
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
	printf("helloaad\n");
	if (sphere->transparency)
	{
		printf("transparency\n");
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
		printf("it else\n");
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
					//	float t0, t1;
					//	if (spheres[j].intersect(phit + nhit * bias, lightDirection, t0))
						if (sp_itsc(v3_sub((*spheres)[j].center, v3_add(phit, v3_muls(nhit, bias))), &light_dir, sphere))
						{
							transmission = vec3(0, 0, 0);
							break;
						}
					}
				}
			//	surfaceColor += sphere->surfaceColor * transmission *
//std::max(float(0), nhit.dot(lightDirection)) * spheres[i].emissionColor;
			//	scolor = v3_dot
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

	//Trace Rays
	printf("In Render...Before tracing rays\n");
	//unsigned char	*pic;
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img;
	char	*img_ptr;
	int 	bpp;
	int 	sl;
	int 	endian;

	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, height, width, "Ray Tracer");
	img = mlx_new_image(mlx_ptr, height, width);
	img_ptr = mlx_get_data_addr(mlx_ptr, &bpp, &sl, &endian);
	//pic = (unsigned char *)malloc(sizeof(t_vec3) * width * height);
	int pos;
	while (++y < height)
	{
	//	printf("In Render...First Loop in the y-dimension\n");
		x = -1;
		while (++x < width && ++pixel)
		{
		//	printf("In Render...Second Loop in the x-dimension\nX == %d\n", x);
			float xx = (2 * ((x + 0.5) * (1 /(float)width)) - 1) * angle * ar;
			float yy = (1 - 2 * ((y + 0.5) * (1 / (float)height)) - 1) * angle;
			t_vec3 raydir = vec3(xx, yy, -1);
			raydir = v3_norm(raydir);
			t_vec3 new_ray = vec3(0, 0, 0);
			*pixel = trace(&new_ray, &raydir, spheres, 0);
		}
	}
	int i = -1;
	x = -1;
	y = -1;
	//while (++i < bpp)
	//{
	while (++y < width)
	{
		while (++x < width)
		{
			pos = (x *  bpp / 8) + (y * sl);
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
				img_ptr[pos] = (char)min(1.0, (image[i]).z) * 255;
				img_ptr[pos + 1] = (char)min(1.0, (image[i]).y) * 255;
				img_ptr[pos + 2] = (char)min(1.0, (image[i]).x) * 255;
					/*img_ptr[pos] = (char)min(1.0, (*pixel).x) >> (bpp - ((i + 1) << 3)) & 255;
					img_ptr[pos + 1] = (char)min(1.0, (*pixel).y) >> (bpp - ((i + 1) << 3)) & 255;
			 		img_ptr[pos + 2] = (char)min(1.0, (*pixel).z) >> (bpp - ((i + 1) << 3)) & 255;*/
			}
		}
		i++;
	}
	printf("In Render...After tracing rays\n");
	saveppm("image.ppm", img_ptr, height, width);
	mlx_put_image_to_window(mlx_ptr, win_ptr, img, 0, 0);
//	mlx_loop(mlx_ptr);
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

	printf("Beginning...\n");
	spheres[0] = new_sphere(vec3(0.0, -10004, -20), 10000, vec3(0.20, 0.20, 0.20), 0, 0);
	spheres[1] = new_sphere(vec3(0.0, 20, -30), 3, vec3(0.0, 0.0, .0), 0, 0);
	spheres[1].ecolor = vec3(3, 3, 3);
	sp = spheres;
	render(&sp);
	return 0;
}