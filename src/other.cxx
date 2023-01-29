#include <random>
#include "../include/other.h"

float generateRandom(float left, float right)
{
    static std::mt19937 gen;
    static std::uniform_real_distribution<float> dis(left, right);
    auto res = dis(gen);
    return (float)res;
}

AFei::vec3<float> randomInUnitSphere()
{
    AFei::vec3<float> res;
    do
    {
        res = 2.0f * AFei::vec3<float>(generateRandom(-1.0f, 1.0f), generateRandom(-1.0f, 1.0f), generateRandom(-1.0f, 1.0f)) - AFei::vec3<float>(1.0f, 1.0f, 1.0f);
    } while (res.length() > 1);
    return res;
}