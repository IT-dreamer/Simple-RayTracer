#include <iostream>
#include "../include/vec3.hxx"

int main(int argc, char **argv)
{
    using namespace AFei;
    vec3 t(9, 1, 0);
    t = 5 * t;
    t /= 5;
    std::cout << "(" << t.x << ", " << t.y << ", " << t.z << ")" << std::endl;
    return EXIT_SUCCESS;
}
