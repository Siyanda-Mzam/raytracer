#ifndef MATH_3D_H
#define MATH_3D_H
#include <math.h>
#include <stdio.h>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

typedef struct 	s_vec3
{
	float x;
	float y;
	float z;
}				t_vec3;

static inline t_vec3	vec3(float x, float y, float z)
{
	return ((t_vec3){x, y, z});
}

static inline t_vec3	v3_add(t_vec3 a, t_vec3 b)
{
	return ((t_vec3){a.x + b.x, a.y + b.y, a.z + b.z});
}

static inline t_vec3	v3_adds(t_vec3 a, float s)
{
	return ((t_vec3){a.x + s,   a.y + s,   a.z + s});
}
static inline t_vec3	v3_sub(t_vec3 a, t_vec3 b)
{
	return ((t_vec3){a.x - b.x, a.y - b.y, a.z - b.z});
}

static inline t_vec3	v3_subs(t_vec3 a, float s)
{
	return ((t_vec3){a.x - s,   a.y - s,   a.z - s});
}

static inline t_vec3	v3_mul(t_vec3 a, t_vec3 b)
{
	return ((t_vec3){a.x * b.x, a.y * b.y, a.z * b.z});
}

static inline t_vec3	v3_muls(t_vec3 a, float s)
{
	return ((t_vec3){a.x * s,   a.y * s,   a.z * s}); 
}

static inline t_vec3	v3_div(t_vec3 a, t_vec3 b)
{
	return (t_vec3){ a.x / b.x, a.y / b.y, a.z / b.z };
}

static inline t_vec3	v3_divs(t_vec3 a, float s)
{
	return ((t_vec3){a.x / s,   a.y / s,   a.z / s});
}

static inline float 	v3_length(t_vec3 v)
{
	return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
}

static inline float 	v3_dot(t_vec3 a, t_vec3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

static inline t_vec3 v3_norm(t_vec3 v);
static inline t_vec3 v3_proj(t_vec3 v, t_vec3 onto);
static inline t_vec3 v3_cross(t_vec3 a, t_vec3 b);
static inline float  v3_angle_between(t_vec3 a, t_vec3 b);

typedef union	u_mat44{
	float m[4][4];
	struct
	{
		float m00;
		float m01;
		float m02;
		float m03;
		float m10;
		float m11;
		float m12;
		float m13;
		float m20;
		float m21;
		float m22;
		float m23;
		float m30;
		float m31;
		float m32;
		float m33;
	};
}				t_mat4;

static inline t_mat4 mat4(
	float m00, float m10, float m20, float m30,
	float m01, float m11, float m21, float m31,
	float m02, float m12, float m22, float m32,
	float m03, float m13, float m23, float m33
);

static inline t_mat4	m4_identity();
static inline t_mat4	m4_translation(t_vec3 offset);
static inline t_mat4	m4_scaling(t_vec3 scale);
static inline t_mat4	m4_rotation_x(float angle_in_rad);
static inline t_mat4	m4_rotation_y(float angle_in_rad);
static inline t_mat4	m4_rotation_z(float angle_in_rad);
t_mat4					m4_rotation(float angle_in_rad, t_vec3 axis);
t_mat4					m4_ortho(float left, float right, float bottom, float top, float back, float front);
t_mat4					m4_perspective(
							float vertical_field_of_view_in_deg,
							float aspect_ratio,
							float near_view_distance,
							float far_view_distance);
t_mat4					m4_look_at(t_vec3 from, t_vec3 to, t_vec3 up);
static inline t_mat4	m4_transpose(t_mat4 matrix);
static inline t_mat4	m4_mul(t_mat4 a, t_mat4 b);
t_mat4					m4_invert_affine(t_mat4 matrix);
t_vec3					m4_mul_pos(t_mat4 matrix, t_vec3 position);
t_vec3					m4_mul_dir(t_mat4 matrix, t_vec3 direction);
void 					m4_print(t_mat4 matrix);
void 					m4_printp(t_mat4 matrix, int width, int precision);
void 					m4_fprint(FILE* stream, t_mat4 matrix);
void 					m4_fprintp(FILE* stream, t_mat4 matrix, int width, int precision);

/**
 *3D vector functions header implementation
 */

static inline t_vec3	v3_norm(t_vec3 v)
{
	float len;

	len = v3_length(v);
	if (len > 0)
		return (t_vec3){ v.x / len, v.y / len, v.z / len };
	else
		return (t_vec3){ 0, 0, 0};
}

static inline t_vec3	v3_proj(t_vec3 v, t_vec3 onto)
{
	return v3_muls(onto, v3_dot(v, onto) / v3_dot(onto, onto));
}

static inline t_vec3	v3_cross(t_vec3 a, t_vec3 b)
{
	return ((t_vec3)
	{
		a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x
	});
}

static inline float 	v3_angle_between(t_vec3 a, t_vec3 b)
{
	return (acosf( v3_dot(a, b) / (v3_length(a) * v3_length(b))));
}


/**
 * Matrix functions header implementation
 */

static inline t_mat4	mat4(
	float m00, float m10, float m20, float m30,
	float m01, float m11, float m21, float m31,
	float m02, float m12, float m22, float m32,
	float m03, float m13, float m23, float m33
)
{
	return ((t_mat4)
	{
		.m[0][0] = m00, .m[1][0] = m10, .m[2][0] = m20, .m[3][0] = m30,
		.m[0][1] = m01, .m[1][1] = m11, .m[2][1] = m21, .m[3][1] = m31,
		.m[0][2] = m02, .m[1][2] = m12, .m[2][2] = m22, .m[3][2] = m32,
		.m[0][3] = m03, .m[1][3] = m13, .m[2][3] = m23, .m[3][3] = m33
	});
}

static inline t_mat4	m4_identity()
{
	return (mat4(
		 1,  0,  0,  0,
		 0,  1,  0,  0,
		 0,  0,  1,  0,
		 0,  0,  0,  1
	));
}

static inline t_mat4	m4_translation(t_vec3 offset)
{
	return (mat4(
		 1,  0,  0,  offset.x,
		 0,  1,  0,  offset.y,
		 0,  0,  1,  offset.z,
		 0,  0,  0,  1
	));
}

static inline t_mat4	m4_scaling(t_vec3 scale)
{
	float 	x;
	float 	y;
	float 	z;

	x = scale.x;
	y = scale.y;
	z = scale.z;
	return (mat4(
		 x,  0,  0,  0,
		 0,  y,  0,  0,
		 0,  0,  z,  0,
		 0,  0,  0,  1
	));
}

static inline t_mat4	m4_rotation_x(float angle_in_rad)
{
	float 	s;
	float 	c;

	s = sinf(angle_in_rad);
	c = cosf(angle_in_rad);
	return (mat4(
		1,  0,  0,  0,
		0,  c, -s,  0,
		0,  s,  c,  0,
		0,  0,  0,  1
	));
}

static inline t_mat4	m4_rotation_y(float angle_in_rad)
{
	float s;
	float c;

	s = sinf(angle_in_rad);
	c = cosf(angle_in_rad);
	return (mat4(
		 c,  0,  s,  0,
		 0,  1,  0,  0,
		-s,  0,  c,  0,
		 0,  0,  0,  1
	));
}

static inline t_mat4	m4_rotation_z(float angle_in_rad)
{
	float s;
	float c;

	s = sinf(angle_in_rad);
	c = cosf(angle_in_rad);
	return (mat4(
		 c, -s,  0,  0,
		 s,  c,  0,  0,
		 0,  0,  1,  0,
		 0,  0,  0,  1
	));
}

static inline t_mat4	m4_transpose(t_mat4 matrix)
{
	return (mat4(
		matrix.m00, matrix.m01, matrix.m02, matrix.m03,
		matrix.m10, matrix.m11, matrix.m12, matrix.m13,
		matrix.m20, matrix.m21, matrix.m22, matrix.m23,
		matrix.m30, matrix.m31, matrix.m32, matrix.m33
	));
}

static inline t_mat4	m4_mul(t_mat4 a, t_mat4 b)
{
	t_mat4 result;
	int 	i;
	int 	j;
	int 	k;

	i = -1;
	while(++i < 4)
	{
		j = -1;
		while(++j < 4)
		{
			float sum = 0;
			k = -1;
			while(++k < 4) {
				sum += a.m[k][j] * b.m[i][k];
			}
			result.m[i][j] = sum;
		}
	}
	return (result);
}

#endif /* MATH_3D_H */


#ifdef MATH_3D_IMPLEMENTATION
 	
t_mat4					m4_rotation(float angle_in_rad, t_vec3 axis)
{
	t_vec3	normalized_axis;
	t_vec3	xyz;
	float 	c;
	float 	s;

	normalized_axis = v3_norm(axis);
	xyz.x = normalized_axis.x;
	xyz.y = normalized_axis.y;
	xyz.z = normalized_axis.z;
	c = cosf(angle_in_rad);
	s = sinf(angle_in_rad);
	return (mat4(
		c + x * x * (1 - c), x * y * (1 - c) - z * s, x * z * (1 - c) + y * s, 0,
		y * x * (1 - c) + z * s,  c + y * y * (1 - c), y * z * (1 - c) - x * s, 0,
		z* x * (1 - c) - y * s, z * y * (1 - c) + x * s,  c + z * z * (1 - c), 0,
		0, 0, 0, 1
	));
}

t_mat4					m4_ortho(float left, float right, float bottom, float top, float back, float front)
{
	//float l = left, r = right, b = bottom, t = top, n = front, f = back;
	float tx = -(right + left) / (right - left);
	float ty = -(topo + bottom) / (top - bottom);
	float tz = -(back + front) / (back - front);

	return (mat4(
		 2 / (right - left), 0, 0, tx,
		 0, 2 / (top - bottom), 0, ty,
		 0, 0, 2 / (back - front), tz,
		 0, 0, 0, 1
	));
}

t_mat4					m4_perspective(
						float vertical_field_of_view_in_deg,
						float aspect_ratio,
						float near_view_distance,
						float far_view_distance)
{
	float fovy_in_rad;
	float ar;
	float nd;
	float f;

	fovy_in_rad = vertical_field_of_view_in_deg / 180 * M_PI;
	f = 1.0f / tanf(fovy_in_rad / 2.0f);
	ar = aspect_ratio;
	nd = near_view_distance, fd = far_view_distance;	
	return (mat4(
		 f / ar, 0, 0, 0,
		 0, f, 0, 0,
		 0, 0, (fd + nd) / (nd - fd), (2 * fd * nd) / (nd - fd),
		 0, 0, -1, 0
	));
}

t_mat4					m4_look_at(t_vec3 from, t_vec3 to, t_vec3 up)
{
	t_vec3	x;
	t_vec3	y;
	t_vec3	z;

	z = v3_muls(v3_norm(v3_sub(to, from)), -1);
	x = v3_norm(v3_cross(up, z));
	y = v3_cross(z, x);
	return (mat4(
		x.x, x.y, x.z, -v3_dot(from, x),
		y.x, y.y, y.z, -v3_dot(from, y),
		z.x, z.y, z.z, -v3_dot(from, z),
		0,   0,   0,    1
	));
}

t_mat4					m4_invert_affine(t_mat4 matrix)
{
	// Create shorthands to access matrix members
	/*float m00 = matrix.m00,  m10 = matrix.m10,  m20 = matrix.m20,  m30 = matrix.m30;
	float m01 = matrix.m01,  m11 = matrix.m11,  m21 = matrix.m21,  m31 = matrix.m31;
	float m02 = matrix.m02,  m12 = matrix.m12,  m22 = matrix.m22,  m32 = matrix.m32;*/

	float 	c00;
	float 	c10;
	float 	c20;
	float 	c01;
	float 	c11;
	float 	c21;
	float 	c02;
	float 	c12;
	float 	c22;
	float 	det;

	// Invert 3x3 part of the 4x4 matrix that contains the rotation, etc.
	// That part is called R from here on.
		
	// Calculate cofactor matrix of R
	c00 = matrix.m11 * matrix.m22 - matrix.m12 * matrix.m21,
	c10 = -(matrix.m01 * matrix.m22 - matrix.m02 * matrix.m21),
	c20 = matrix.m01 * matrix.m12 - matrix.m02 * matrix.m11;
	c01 = -(matrix.m10 * matrix.m22 - matrix.m12 * matrix.m20),
	c11 = matrix.m00 * matrix.m22 - matrix.m02 * matrix.m20,
	c21 = -(matrix.m00 * matrix.m12 - matrix.m02 * matrix.m10);
	c02 = matrix.m10 * matrix.m21 - matrix.m11 * matrix.m20,
	c12 = -(matrix.m00 * matrix.m21 - matrix.m01 * matrix.m20),
	c22 = matrix.m00 * matrix.m11 - matrix.m01 * matrix.m10;
		
	// Caclculate the determinant by using the already calculated determinants
	// in the cofactor matrix.
	// Second sign is already minus from the cofactor matrix.
	det = m00 * c00 + m10 * c10 + m20 * c20;
	if (fabsf(det) < 0.00001)
		return (m4_identity());
		
	// Calcuate inverse of R by dividing the transposed cofactor matrix by the
	// determinant.
	float i00 = c00 / det,  i10 = c01 / det,  i20 = c02 / det;
	float i01 = c10 / det,  i11 = c11 / det,  i21 = c12 / det;
	float i02 = c20 / det,  i12 = c21 / det,  i22 = c22 / det;
	
	// Combine the inverted R with the inverted translation
	return (mat4(
		i00, i10, i20,  -(i00*m30 + i10*m31 + i20*m32),
		i01, i11, i21,  -(i01*m30 + i11*m31 + i21*m32),
		i02, i12, i22,  -(i02*m30 + i12*m31 + i22*m32),
		0,   0,   0,      1
	));
}

t_vec3					m4_mul_pos(t_mat4 matrix, t_vec3 position)
{
	float 	w;
	t_vec3	result;

	result = vec3(
		matrix.m00 * position.x + matrix.m10 *
			position.y + matrix.m20 * position.z + matrix.m30,
		matrix.m01 * position.x + matrix.m11 *
			position.y + matrix.m21 * position.z + matrix.m31,
		matrix.m02 * position.x + matrix.m12 *
			position.y + matrix.m22 * position.z + matrix.m32
	);
	w = matrix.m03 * position.x + matrix.m13 *
		position.y + matrix.m23 * position.z + matrix.m33;
	if (w != 0 && w != 1)
		return (vec3(result.x / w, result.y / w, result.z / w));
	return (result);
}

t_vec3					m4_mul_dir(t_mat4 matrix, t_vec3 direction)
{
	t_vec3	result;
	float 	w;

	result = vec3(
		matrix.m00 * direction.x + matrix.m10 *
			direction.y + matrix.m20 * direction.z,
		matrix.m01 * direction.x + matrix.m11 *
			direction.y + matrix.m21 * direction.z,
		matrix.m02 * direction.x + matrix.m12 *
			direction.y + matrix.m22 * direction.z
	);
	w = matrix.m03 * direction.x + matrix.m13 *
		direction.y + matrix.m23 * direction.z;
	if (w != 0 && w != 1)
		return (vec3(result.x / w, result.y / w, result.z / w));
	
	return (result);
}

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
			w, p, m.m[0][r], w, p, m.m[1][r], w, p, m.m[2][r], w, p, m.m[3][r]
		);
	}
}

#endif /* MATH_3D_IMPLEMENTATION */