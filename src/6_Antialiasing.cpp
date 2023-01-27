#include "../include/hitableList.hxx"
#include "../include/sphere.hxx"
#include "../include/camera.hxx"
#include <fstream>
#include <iostream>
#include <cfloat>
#include <random>

using AFei::vec3;
using AFei::ray;
using AFei::sphere;
using AFei::hitableList;
using AFei::camera;

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

inline float random0To1()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0f, 1.0f);
    auto res = dis(gen);
    return (float)res;
}

template<class T>
vec3<float> color(ray<T> &r, hitableList *l)
{
    hitRecord rec;
    if(l->hit(r, 0.0f, FLT_MAX, rec))
    {
        auto N = rec.normal;
        if(rec.obNumber == 0) N += 1.0f;
        N *= 0.5f;
        return N;
    }
    else
    {
        float t = 0.5f * r.direction.y + 1.0f;
        return vec3<float>(1.0f, 1.0f, 1.0f) * (1.0f - t) + vec3<float>(0.5f, 0.7f, 1.0f) * t;
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

    int ns = 32;

    for(int i = heigth - 1; i >= 0; i--)
    {
        for(int j = 0; j < width; j++)
        {
            vec3<float> clr(0.0f, 0.0f, 0.0f);
            for(int k = 0; k < ns; k++)
            {
                float u = float(j + random0To1()) / (float)width;
                float v = float(i + random0To1()) / (float)heigth;
                auto myRay = cam.get_ray(u, v);
                clr += color(myRay, world);
            }
            clr /= (float)ns;
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

