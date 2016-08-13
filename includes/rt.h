#include "matlib.h"
#include "mlx.h"
#define TRUE 1
#define FALSE 0
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

float			max(float i, float j);
float			min(float i, float j);
t_bool			sp_itsc(const t_vec3 diff, const t_vec3 *ray_dir, 
						t_sphere *sphere);
float			mix(float a, float b, float mix);
t_vec3			trace(t_vec3 *ray_origin, t_vec3 *ray_dir, t_sphere
						**spheres, const int *depth);
void			saveppm(char *fname, char *image, int height, int width);
void			render(t_sphere **spheres);
t_sphere		new_sphere(t_vec3 pos, float radius, t_vec3 scolor, int refl, int trans);