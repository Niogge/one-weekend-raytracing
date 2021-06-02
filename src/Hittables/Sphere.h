#pragma once
#include "../Utils/FWDUtils.h"
#include "../Utils/Math/vec3.h"
#include "Hittable.h"
BEGIN_NAMESPACE
class Sphere:hittable
{
public:
	Sphere() :center(vec3(0,0,0)), radius(1.0) {};
	Sphere(vec3& c, double d): center(c), radius(d) {};
	virtual bool hit(const Ray& r, double t_min, double t_max, hit_record& rec) const;
public:
	point3 center;
	double radius;
};
END_NAMESPACE