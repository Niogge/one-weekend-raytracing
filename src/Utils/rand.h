#pragma once
#include <random>
inline double random_double()
{
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
}
inline double random_double(double min, double max)
{
    double rand = random_double()*(max - min)+min;
    return rand;
}