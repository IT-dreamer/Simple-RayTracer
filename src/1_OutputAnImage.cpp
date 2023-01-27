#include <fstream>
#include <iostream>

int main(void)
{
    std::ofstream outFile;
    outFile.open("../temp/out.ppm", std::ios::out | std::ios::trunc);
    int nx = 100;
    int ny = 200;

    outFile << "P3" << std::endl;
    outFile << ny << " " << nx << std::endl;
    outFile << "255" << std::endl;

    for(int i = 0; i < nx; i++)
    {
        for(int j = 0; j < ny; j++)
        {
            float r = float(i) / float(nx);
            float g = float(j) / float(ny);
            float b = 0.2;
            int ir = int(255.99 * r);
            int ig = int(255.99 * g);
            int ib = int(255.99 * b);
            outFile << ir << " " << ig << " " << ib << std::endl;
        }
    }

    outFile.close();
    return EXIT_SUCCESS;
}