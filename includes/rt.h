#include "matlib.h"
#define TRUE 1
#define FALSE 0
#define INFINITY 1e8
#define MAX_RAY_DEPTH 5

typedef int 	t_bool;

typedef struct 	s_object
{
	t_vec3	center;
	t_vec3	scolor;
	t_vec3	ecolor;
	float	radius;
	float	radius2;
	float	transparency;
	float	reflection;
	float	roots[2];
}				t_sphere;

t_bool			sp_itsc(const t_vec3 diff,
						const t_vec3 &ray_dir, 
						t_sphere sphere);
float			mix(const float *a, const float *b, const float *mix);
t_vec3			trace(t_vec3 *ray_origin, t_vec3 *ray_dir, t_sphere
						**spheres, const int *depth);