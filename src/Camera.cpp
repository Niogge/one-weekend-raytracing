#include "Camera.h"
#include "Utils/Math/MathUtils.h"
#include "Utils/Math/Ray.h"
USE_NAMESPACE(camera)::camera()
{
	auto aspect_ratio = 16.0 / 9.0;
	auto viewport_height = 2.0;
	auto viewport_width = aspect_ratio * viewport_height;
	auto focal_length = 1.0;

	origin = point3(0, 0, 0);
	horizontal = vec3(viewport_width, 0.0, 0.0);
	vertical = vec3(0.0, viewport_height, 0.0);
	lower_left_corner = origin - horizontal / 2 - vertical / 2 - vec3(0, 0, focal_length);
}

USE_NAMESPACE(camera)::camera(point3 lookfrom, point3 lookat, vec3 up, double vfov, double aspect_ratio)
{
	auto theta = degrees_to_radians(vfov);
	auto h = tan(theta / 2);
	auto viewport_height = 2.0 * h;
	auto viewport_width = aspect_ratio * viewport_height;
	auto focal_length = 1.0;



	auto w = (lookfrom - lookat).normalized();
	auto u = cross(up, w).normalized();
	auto v = cross(w, u);

	origin = lookfrom;
	horizontal = viewport_width * u;
	vertical = viewport_height * v;
	lower_left_corner = origin - horizontal / 2 - vertical / 2 - w;
}

USE_NAMESPACE(Ray) USE_NAMESPACE(camera)::get_ray(double u, double v) const
{
	return Ray(origin, lower_left_corner + u * horizontal + v * vertical - origin);
}
