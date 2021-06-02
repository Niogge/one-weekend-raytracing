#pragma once
#include <cmath>
#include <iostream>

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
