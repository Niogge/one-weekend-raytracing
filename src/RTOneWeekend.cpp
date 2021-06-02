

#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include "Includes/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "Includes/stb_image_write.h"
#include <vector>
#include "Utils/IOUtils.h"
#include "Utils/Color.h"
#include "Utils/Math/Ray.h"
#include "Utils/FWDUtils.h"
#include "Hittables/Sphere.h"


#define IMG_CHANNELS 3

BEGIN_NAMESPACE

RGBColor ray_color(const Ray& r, const Sphere& s)
{
	
	hit_record rec;
	if (s.hit(r, 0, 10000, rec))
	{
		vec3 N = rec.normal.normalized();
		return 0.5 * RGBColor(N.x() + 1, N.y() + 1, N.z() + 1);
	}
	vec3 unit_direction = r.direction().normalized();
	auto t = 0.5 * (unit_direction.y() + 1.0);
	return (1.0 - t) * RGBColor(1.0, 1.0, 1.0) + t * RGBColor(0.5, 0.7, 1.0);
}
int main_rt()
{
	//target image
	const auto aspect_ratio = 16.0 / 9.0;
	const int image_width = 1920;
	const int image_height = static_cast<int>(image_width / aspect_ratio);

	//camera
	auto viewport_height = 2.0;
	auto viewport_width = aspect_ratio * viewport_height;
	auto focal_length = 1.0;
	auto origin = point3(0, 0, 0);
	auto horizontal = vec3(viewport_width, 0, 0);
	auto vertical = vec3(0, viewport_height, 0);
	auto lower_left_corner = origin - horizontal / 2 - vertical / 2 - vec3(0, 0, focal_length);

	std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";
	std::vector<uint8_t> pixel_data;
	vec3 center(0.0, 0.0, -1.0);
	Sphere s(center, 0.5);
	for (int j = image_height - 1; j >= 0; --j)
	{
		//PROGRESS_CERR("Scanlines Remaining", j);
		PROGRESS_PERCENTAGE("Scanline progress", image_height - j, image_height);
		for (int i = 0; i < image_width; i++)
		{
			auto u = double(i) / (image_width - 1);
			auto v = double(j) / (image_height - 1);
			Ray r = Ray(origin, lower_left_corner + u * horizontal + v * vertical);
			RGBColor pixel_color = ray_color(r, s);
			write_color(pixel_color, pixel_data);
		}
	}
	stbi_write_png("test.png", image_width, image_height, IMG_CHANNELS, pixel_data.data(), IMG_CHANNELS * image_width);
	PROGRESS_COMPLETE;
	return 0;
}

END_NAMESPACE

int main()
{
	USE_NAMESPACE(main_rt)();
}