#include "Ray.h"

point3 Ray::origin() const
{
    return orig;
}

vec3 Ray::direction() const
{
    return dir;
}

point3 Ray::at(double t) const
{
    return orig + t * dir;
}
