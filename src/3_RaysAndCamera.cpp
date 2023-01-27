#include "../include/ray.hxx"
#include "../include/vec3.hxx"
#include <fstream>
#include <iostream>

using AFei::vec3;
using AFei::ray;

vec3<int> color(ray<float> &r)
{
    float t = 0.5 * r.direction.y + 1.0;
    float ir = (1 - t) * 1.0 + t * 0.5;
    float ig = (1 - t) * 1.5 + t * 0.7;
    float ib = (1 - t) * 1.6 + t * 0.6;
    ir *= 255.99;
    ig *= 255.99;
    ib *= 255.99;
    return vec3<int>((int)ir, (int)ig, (int)ib);
}

int main(void)
{
    std::ofstream outFile;
    outFile.open("../temp/out.ppm", std::ios::out | std::ios::trunc);
    int nx = 100;
    int ny = 200;

    outFile << "P3" << std::endl;
    outFile << ny << " " << nx << std::endl;
    outFile << "255" << std::endl;

    vec3<float> lowerLeftCorner(-2.0, -1.0, -1.0);
    vec3<float> horizontal(4.0, 0.0, 0.0);
    vec3<float> vertical(0.0, 2.0, 0.0);
    vec3<float> origin(0.0, 0.0, 0.0);

    for(int i = 0; i < nx; i++)
    {
        for(int j = 0; j < ny; j++)
        {
            float u = (float)i / (float)nx;
            float v = (float)j / (float)ny;
            auto dir = (lowerLeftCorner + u * horizontal + v * vertical).normal_vector();
            ray<float> myRay(origin, dir);
            auto clr = color(myRay);
            outFile << clr.x << " " << clr.y << " " << clr.z << " ";
        }
        outFile << std::endl;
    }

    outFile.close();
    return EXIT_SUCCESS;
}

