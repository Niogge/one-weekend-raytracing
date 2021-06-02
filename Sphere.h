#pragma once
#include "FWDUtils.h"
#include "vec3.h"
BEGIN_NAMESPACE
FWD_DECL(Ray)
class Sphere
{
public:
	Sphere() :center(vec3(0,0,0)), radius(1.0) {};
	Sphere(vec3& c, double d): center(c), radius(d) {};
	double ray_sphere_intersection(const Ray& r) const;
public:
	point3 center;
	double radius;
};
END_NAMESPACE