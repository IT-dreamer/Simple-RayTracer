#include <random>
#include "../include/other.h"

float generateRandom(float left, float right)
{
    static std::mt19937 gen;
    static std::uniform_real_distribution<float> dis(left, right);
    auto res = dis(gen);
    return (float)res;
}