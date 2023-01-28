#include <fstream>
#include <iostream>
#include <cfloat>
#include <random>
#include "../include/ray.hxx"
#include "../include/vec3.hxx"
#include "../include/camera.hxx"
#include "../include/sphere.hxx"
#include "../include/hitableList.hxx"
#include "../include/other.h"

using AFei::vec3;
using AFei::ray;
using AFei::sphere;
using AFei::hitableList;
using AFei::camera;

vec3<float> randomInUnitSphere()
{
    vec3<float> res;
    do
    {
        res = 2.0f * vec3<float>(generateRandom(-1.0f, 1.0f), generateRandom(-1.0f, 1.0f), generateRandom(-1.0f, 1.0f)) - vec3<float>(1.0f, 1.0f, 1.0f);
    } while (res.length() > 1);
    return res;
}

template<class T>
vec3<float> color(ray<T> &r, hitableList *l)
{
    hitRecord rec;
    if(l->hit(r, 0.0f, FLT_MAX, rec))
    {
        auto target = randomInUnitSphere().normal_vector();
        target = target + (rec.intersectPoint + rec.normal);
        ray<T> reflect_ray(rec.intersectPoint, (target - rec.intersectPoint).normal_vector());
        return color(reflect_ray, l) * 0.5f;
    }
    else
    {
        float t = 0.5f * r.direction.y + 1.0f;
        return vec3<float>(1.0f, 1.0f, 1.0f) * (1.0f - t) + vec3<float>(0.5f, 0.7f, 1.0f) * t;
    }
}

void progressBar(int quantity, int total_amount)
{
    static char buffer[101] = {0};
    static char arr[5] = {"-/|\\"};
    static float total_progress = 0.0f;
    static int i = 0;
    float current_progress = (float)quantity / (float)total_amount;

    if(current_progress > total_progress)
    {
        buffer[i] = '#';
        fprintf(stdout, "[%-100s][%d%%][%c]\r",buffer,i,arr[i%4]);
        fflush(stdout);
        total_progress += 0.01f;
        i += 1;
    }
}

int main(void)
{
    std::ofstream outFile;
    outFile.open("../temp/out.ppm", std::ios::out | std::ios::trunc);
    int heigth = 400;
    int width = 800;

    outFile << "P3" << std::endl;
    outFile << width << " " << heigth << std::endl;
    outFile << "255" << std::endl;

    vec3<float> horizontal(4.0, 0.0, 0.0);  //水平向量
    vec3<float> vertical(0.0, 2.0, 0.0);    //垂直向量
    vec3<float> lowerLeftCorner(-2.0, -1.0, -1.0);
    vec3<float> origin(0.0, 0.0, 0.0);

    camera cam(origin, lowerLeftCorner, horizontal, vertical);

    hiTabel *list[2];
    list[0] = new sphere(vec3<float>(0.0f, 0.0f, -1.0f), 0.5);
    list[1] = new sphere(vec3<float>(0.0f, -50.5f, -1.0f), 50.0f);
    hitableList *world = new hitableList(2, list);

    int ns = 4;

    for(int i = heigth - 1; i >= 0; i--)
    {
        for(int j = 0; j < width; j++)
        {
            vec3<float> clr(0.0f, 0.0f, 0.0f);
            for(int k = 0; k < ns; k++)
            {
                float u = float(j + generateRandom(0.0f, 1.0f)) / (float)width;
                float v = float(i + generateRandom(0.0f, 1.0f)) / (float)heigth;
                auto myRay = cam.get_ray(u, v);
                clr += color(myRay, world);
            }
            clr /= (float)ns;
            clr = vec3<float>((float)sqrt(clr.x), (float)sqrt(clr.y), (float)sqrt(clr.z));
            int ir = int(255.99 * clr.x);
            int ig = int(255.99 * clr.y);
            int ib = int(255.99 * clr.z);
            outFile << ir << " " << ig << " " << ib << std::endl;
        }
        progressBar(heigth - i, heigth);
    }

    outFile.close();
    std::cout << std::endl;
    return EXIT_SUCCESS;
}