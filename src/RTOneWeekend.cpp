

#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include "Includes/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "Includes/stb_image_write.h"
#include <vector>
#include "Utils/FWDUtils.h"
#include "Utils/IOUtils.h"
#include "Utils/Color.h"
#include "Utils/Math/Ray.h"
#include "Hittables/Sphere.h"
#include "Hittables/Model.h"
#include "Hittables/HittableList.h"
#include "Utils/rand.h"
#include "Materials/Material.h"
#include "Materials/Lambertian.h"
#include "Materials/Metal.h"
#include "Materials/Dielectric.h"

#include "Camera.h"
#include <memory>


#define IMG_CHANNELS 3

BEGIN_NAMESPACE

RGBColor ray_color(const Ray& r, const hittable& world, int depth)
{
	if (depth <= 0)
	{
		return RGBColor(0, 0, 0);
	}
	hit_record rec;
	if (world.hit(r, 0.001, 10000, rec))
	{
		Ray scattered;
		RGBColor attenuation;
		if (rec.mat_ptr->scatter(r, rec, attenuation, scattered))
		{
			return attenuation * ray_color(scattered, world, depth - 1);
		}
		return RGBColor(0, 0, 0);
		/*point3 target = rec.p  + random_in_hemisphere(rec.normal);
		return 0.5 * ray_color(Ray(rec.p, target - rec.p), world, depth-1);*/
		/*vec3 N = rec.normal.normalized();
		return 0.5 * RGBColor(N.x() + 1, N.y() + 1, N.z() + 1);*/
	}
	vec3 unit_direction = r.direction().normalized();
	auto t = 0.5 * (unit_direction.y() + 1.0);
	return (1.0 - t) * RGBColor(1.0, 1.0, 1.0) + t * RGBColor(0.5, 0.7, 1.0);
}
int main_rt()
{
	//target image
	const auto aspect_ratio = 16.0 / 9.0;
	const int image_width = 400;
	const int image_height = static_cast<int>(image_width / aspect_ratio);
	const int sample_per_pixel = 20;
	const int max_depth = 50;
	//world 
	hittable_list world;

	shared_ptr<material> metal_purple = make_shared<metal>(RGBColor(0.83, 0.59, 0.98), 0.3);
	shared_ptr<material> lambert_green = make_shared<lambertian>(RGBColor(93. / 255, 240. / 255, 67. / 255));
	shared_ptr<material> full_glass = make_shared<dielectric>(RGBColor(0.8, 0.8, 1), 1.5);
	shared_ptr<material> hollow_glass = make_shared<dielectric>(RGBColor(1, 1, 1), 1.2);// the hollowness is with the negative radius of the sphere 
	//world.add(std::make_shared<Sphere>(vec3(-0.5,-0.1,-1.0),0.5, lambert_green));
	//world.add(std::make_shared<Sphere>(vec3(0.5, 0.1, -1.1), 0.5, metal_purple));
	//world.add(std::make_shared<Sphere>(vec3(-0.1, 0.2, -0.5), 0.12, full_glass));
	//world.add(std::make_shared<Sphere>(vec3(0, -0.05, -0.2), -0.05, hollow_glass));
	
	world.add(std::make_shared<Model>("assets\\teapot.obj", vec3(0, 0, 0), metal_purple));
	//camera
	camera cam(point3(-1, -5, 0), point3(0, 0, -1), vec3(0, 1, 0), 30, aspect_ratio);

	std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";
	std::vector<uint8_t> pixel_data;


	for (int j = image_height - 1; j >= 0; --j)
	{
		PROGRESS_PERCENTAGE("Scanline progress", image_height - j, image_height);
		for (int i = 0; i < image_width; i++)
		{
			RGBColor pixel_color(0, 0, 0);
			for (int s = 0; s < sample_per_pixel; s++)
			{
				double u = double(i + random_double()) / (image_width - 1);
				double v = double(j + random_double()) / (image_height - 1);
			/*	double u = double(i ) / (image_width - 1);
				double v = double(j ) / (image_height - 1);*/
				Ray r = cam.get_ray(u,v);
				pixel_color += ray_color(r, world,50);
			}
			write_color(pixel_color, pixel_data,sample_per_pixel);
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