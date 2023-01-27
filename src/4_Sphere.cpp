#include "../include/ray.hxx"
#include "../include/vec3.hxx"
#include <fstream>
#include <iostream>

using AFei::vec3;
using AFei::ray;

template<class T>
bool hitSphere(ray<T> &r, const vec3<float> sphereCenter, const float radius)
{
    auto a = dot(r.direction, r.direction);
    auto b = dot(r.original, r.direction - sphereCenter) * 2;
    auto c = dot(r.direction - sphereCenter, r.direction - sphereCenter) - radius * radius;
    if(b * b - 4 * a * c > 0)
    {

        return true;
    }
        
    else
        return false;
}

template<class T>
vec3<int> color(ray<T> &r)
{
    if(hitSphere(r, vec3<float>(0.0, 0.0, -1.0), 0.5))
        return vec3<int>(255, 0, 255);
    else
    {
        T t = 0.5 * r.direction.y + 1.0;
        T ir = (1 - t) * 1.0 + t * 0.5;
        T ig = (1 - t) * 1.5 + t * 0.7;
        T ib = (1 - t) * 1.6 + t * 0.6;
        ir *= 255.99;
        ig *= 255.99;
        ib *= 255.99;
        return vec3<int>((int)ir, (int)ig, (int)ib);
    }
}

int main(void)
{
    std::ofstream outFile;
    outFile.open("../temp/out.ppm", std::ios::out | std::ios::trunc);
    int heigth = 200;
    int width = 400;

    outFile << "P3" << std::endl;
    outFile << width << " " << heigth << std::endl;
    outFile << "255" << std::endl;

    vec3<float> horizontal(4.0, 0.0, 0.0);  //水平向量
    vec3<float> vertical(0.0, 2.0, 0.0);    //垂直向量
    vec3<float> lowerLeftCorner(-2.0, -1.0, -1.0);
    vec3<float> origin(0.0, 0.0, 0.0);

    for(int i = 0; i < heigth; i++)
    {
        for(int j = 0; j < width; j++)
        {
            float v = (float)i / (float)heigth;
            float u = (float)j / (float)width;
            auto dir = (lowerLeftCorner + u * horizontal + v * vertical).normal_vector();
            ray<float> myRay(origin, dir);
            auto clr = color(myRay);
            outFile << clr.x << " " << clr.y << " " << clr.z << std::endl;
        }
    }

    outFile.close();
    return EXIT_SUCCESS;
}

