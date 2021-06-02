#pragma once

#include "Math/vec3.h"
#include <vector>
void write_color(RGBColor color, std::vector<uint8_t>& dest)
{
	dest.push_back(static_cast<uint8_t>(255.999 * color.x()));
	dest.push_back(static_cast<uint8_t>(255.999 * color.y()));
	dest.push_back(static_cast<uint8_t>(255.999 * color.z()));
}