#include "../includes/rt.h"

float		mix(const float *a, const float *b, float *mix)
{
	return (b * mix + a * (1 - mix));
}


static int 	obj_len(t_sphere *spheres)
{
	unsigned int i;

	if (spheres)
	{
		i = 0;
		while (spheres[i])
			i++;
		return (i);
	}
	return (0);
}

t_vec3		trace(t_vec3 *ray_origin, t_vec3 *ray_dir, t_sphere **spheres, const int *depth)
{
	float			near;
	const t_sphere	*sphere;
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
	obj_len = obj_len(*spheres)
	while (++i < obj_len)
	{
		if (sp_itsc(v3_sub((*spheres)[i].center, *ray_origin), *ray_dir, (*spheres)[i]))
		{
			if (spheres[i].roots[0] < 0)
				spheres[i].roots[0] = spheres[i].roots[1];
			if (spheres[i].roots[0] < near)
			{
				near = spheres[i].roots[0];
				sphere = &((*spheres)[i]);
			}
		}
	}
	if (!sphere)
		return (vec3(2.0, 2.0, 2.0));
	scolor = vec3(0.0, 0.0, 0.0);
	phit = v3_add(*ray_origin, v3_muls(*ray_dir, near));
	nhit = v3_sub(phit, sphere.center);
	nhit = v3_norm(nhit);
	bias = 1e-4;
	inside = FALSE;
	if (v3_dot(*ray_dir, nhit) > 0)
	{
		nhit = -nhit;
		inside = TRUE;
	}
	if ((sphere.transparency > 0  || sphere.reflection > 0)
		&& depth < MAX_RAY_DEPTH)
	{
		facingratio = -v3_dot(*ray_dir, nhit);
		fresneleffect = mix(pow(1 - facingratio, 3), 1, 0.1);
	//	Vec3f refldir = raydir - nhit * 2 * raydir.dot(nhit);
		refldir = v3_sub(*ray_dir, v3_muls(nhit, 2 * v3_dot(*ray_dir, nhit)));
		refldir = v3_norm(refldir);
		reflection = trace(v3_add(phit, v3_muls(nhit, bias)), refldir, spheres, depth + 1);
	}
	if (sphere.transparency)
	{
		ior = 1.1;
		if (inside)
			eta = ior;
		else
			eta = 1 / ior;
		cosi = -v3_dot(nhit, *raydir);
		k = 1 - eta  * eta * (1  - cosi  * cosi);
		//Vec3f refrdir = raydir * eta + nhit * (eta * cosi - sqrt(k))
		t_vec3 refrdir = v3_add(v3_muls(*ray_dir, eta), v3_muls(nhit, eta * cosi - sqrt(k)));
		refrdir = v3_norm(refrdir);
	//	refraction = trace(phit - nhit * bias, refrdir, spheres, depth + 1);
		refraction = trace(v3_sub(phit, v3_muls(nhit, bias)), refrdir, spheres, depth + 1);
		float val =  (reflection * fresneleffect * refraction * (1 - fresneleffect) * sphere.transparency) *
					sphere.reflection;
		scolor = v3(val, val, val);
	}
	else
	{
		i = -1;
		while (++i < obj_len)
		{
			if (spheres[i].ecolor.x > 0)
			{
				t_vec3 transmission = 1;
				t_vec3 light_dir = v3_sub(spheres[i].center, phit);
				light_dir = v3_norm(light_dir);
				int 	j = 0;
				while (j < obj_len)
				{
					if (i != j)
					{
						float t0, t1;
					//	if (spheres[j].intersect(phit + nhit * bias, lightDirection, t0))
						if (sp_itsc(v3_sub(spheres[j].center, v3_add(phit, v3_muls(nhit, bias))), light_dir, sphere))
						{
							transmission = 0;
							break;
						}
					}
				}
			}
		}
	}
}