#ifndef COLOR_H
#define COLOR_H

#include "Math/vec3.h"
#include <vector>
inline double clamp(double x, double min, double max)
{
	if (x < min) return min;
	if (x > max) return max;
	return x;
}

void write_color(RGBColor color, std::vector<uint8_t>& dest, int samples_per_pixel)
{
	auto r = color.x();
	auto g = color.y();
	auto b = color.z();

	auto scale = 1.0 / samples_per_pixel;
	r = sqrt(r*scale);
	g = sqrt(g*scale);
	b = sqrt(b*scale);
	dest.push_back(static_cast<uint8_t>(256*clamp(r,0.0,0.999)));
	dest.push_back(static_cast<uint8_t>(256 * clamp(g, 0.0, 0.999)));
	dest.push_back(static_cast<uint8_t>(256 * clamp(b, 0.0, 0.999)));
}
#endif