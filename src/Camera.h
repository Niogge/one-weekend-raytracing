#pragma once
#include "Utils/FWDUtils.h"
#include "Utils/Math/vec3.h"
BEGIN_NAMESPACE
FWD_DECL(Ray);
class camera
{
public:
	camera();
	camera(point3 lookfrom, point3 lookat,vec3 up, double vfov, double aspect_ratio);
	Ray get_ray(double u, double v) const; 
private:
	point3 origin;
	point3 lower_left_corner;
	vec3 horizontal;
	vec3 vertical;
};
END_NAMESPACE