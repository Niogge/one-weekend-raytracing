#ifndef VEC3_H
#define VEC3_H


#include <cmath>
#include <iostream>
#include "../rand.h"
#include "../../Includes/wobj.h"

using std::sqrt;

class vec3
{
public:
	vec3() : e{ 0,0,0 } {}
	vec3(double x, double y, double z) : e{ x,y,z } {}

	double x() const;
	double y() const;
	double z() const;

	vec3 operator-() const;
	double operator[](int i) const;
	double& operator[](int i);
	vec3& operator+=(const vec3& v);
	vec3& operator*=(const double t);
	vec3& operator/=(const double t);
	double length()const;
	double length_squared() const;
	vec3 normalized() const;
	void normalize();
	inline static vec3 random()
	{
		return vec3(random_double(), random_double(), random_double());
	}
	
	inline static vec3 random(double min, double max)
	{
		return vec3(random_double(min, max), random_double(min, max), random_double(min, max));
	}
	
	bool near_zero();

public:
	double e[3];
};

using point3 = vec3; //alias for 3d point;
using RGBColor = vec3;//alias for rgb color

	//utility func
inline std::ostream& operator<<(std::ostream& out, const vec3& v)
{
	return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

inline vec3 operator+(const vec3& u, const vec3& v)
{
	return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

inline vec3 operator-(const vec3& u, const vec3& v)
{
	return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

inline vec3 operator*(const vec3& u, vec3& v)
{
	return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

inline vec3 operator*(const vec3& u, double d)
{
	return vec3(d * u.e[0], d * u.e[1], d * u.e[2]);
}
inline vec3 operator*(double d, const vec3& u)
{
	return u * d;
}
inline vec3 operator/(vec3 v, double t)
{
	return (1 / t) * v;
}
inline double dot(const vec3& u, const vec3& v)
{
	return u.e[0] * v.e[0]
		+ u.e[1] * v.e[1]
		+ u.e[2] * v.e[2];
}
inline vec3 cross(const vec3& u, const vec3& v)
{
	return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
		u.e[2] * v.e[0] - u.e[0] * v.e[2],
		u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

inline vec3 random_in_unit_sphere()
{
	while (true)
	{
		auto p = vec3::random(-1.0, 1.0);
		if (p.length_squared() >= 1) continue;
		return p;
	}
}
inline vec3 random_unit_vector()
{
	return random_in_unit_sphere().normalized();
}
inline vec3 random_in_hemisphere(const vec3& normal)
{
	vec3 in_unit_sphere = random_in_unit_sphere();
	if (dot(in_unit_sphere, normal) > 0)
	{
		return in_unit_sphere;
	}
	else
	{
		return -in_unit_sphere;
	}
}
inline vec3 reflect(const vec3& v, const vec3& n)
{
	return v - 2 * dot(v, n) * n;
}
inline vec3 refract(const vec3& uv, const vec3& n, double etai_over_etat)
{
	auto cos_theta = fmin(dot(-uv, n), 1.0); //a*b*cos(ab)
	vec3 r_out_perp = etai_over_etat * (uv + cos_theta * n);
	vec3 r_out_parallel = -sqrt(fabs(1.0 - r_out_perp.length_squared())) * n;
	return r_out_perp + r_out_parallel;
}
inline vec3 operator*(const vec3& u, const vec3& v)
{
	return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}
inline vec3 from_wobj_to_vec3(const wobj_float3& f3)
{
	return vec3(f3.x, f3.y, f3.z);
}
inline wobj_float3 from_vec3_to_wobj(const vec3& v3)
{
	wobj_float3 f;
	f.x = v3.x();
	f.y = v3.y();
	f.z = v3.z();
	return f;
}
#endif // !VEC3_H