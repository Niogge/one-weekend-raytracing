#include "Ray.h"

point3 USE_NAMESPACE(Ray)::origin() const
{
    return orig;
}

vec3 USE_NAMESPACE(Ray)::direction() const
{
    return dir;
}

point3 USE_NAMESPACE(Ray)::at(double t) const
{
    return orig + t * dir;
}

