#include <random>
#include "../include/other.h"

float generateRandom(float left, float right)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(left, right);
    auto res = dis(gen);
    return (float)res;
}