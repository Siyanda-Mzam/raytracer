#include "../includes/rt.h"

t_bool			sp_itsc(const t_vec3 diff,
						const t_vec3 *ray_dir, 
						t_sphere *sphere)
{
	float	tca;
	float	d2;
	float	thc;

	if ((tca = v3_dot(diff, *ray_dir)) < 0)
		return (FALSE);
	if ((d2 = v3_dot(diff, diff) - tca * tca) > (*sphere).radius2)
		return (FALSE);
	thc = sqrt((*sphere).radius2 - d2);
	(*sphere).roots[0] = tca - thc;
	(*sphere).roots[1] = tca + thc;
	return (TRUE);
}