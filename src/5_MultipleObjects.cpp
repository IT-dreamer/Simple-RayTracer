#include "../include/hitableList.hxx"
#include "../include/sphere.hxx"
#include <fstream>
#include <iostream>
#include <cfloat>

using AFei::vec3;
using AFei::ray;
using AFei::sphere;
using AFei::hitableList;

template<class T>
vec3<int> color(ray<T> &r, hitableList *l)
{
    hitRecord rec;
    if(l->hit(r, 0.0f, FLT_MAX, rec))
    {
        auto N = rec.normal;
        N *= 255.99;
        return vec3<int>((int)N.x, (int)N.y, (int)N.z);
    }
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

    hiTabel *list[2];
    list[0] = new sphere(vec3<float>(0.0f, 0.0f, -1.0f), 0.5);
    list[1] = new sphere(vec3<float>(0.0f, -50.5f, -1.0f), 50.0f);
    hitableList *world = new hitableList(2, list);

    for(int i = heigth - 1; i >= 0; i--)
    {
        for(int j = 0; j < width; j++)
        {
            float u = (float)j / (float)width;
            float v = (float)i / (float)heigth;
            auto dir = (lowerLeftCorner + u * horizontal + v * vertical).normal_vector();
            ray<float> myRay(origin, dir);
            auto clr = color(myRay, world);
            outFile << clr.x << " " << clr.y << " " << clr.z << std::endl;
        }
    }

    outFile.close();
    return EXIT_SUCCESS;
}

