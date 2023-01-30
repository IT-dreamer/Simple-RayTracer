# Overview
This project is a learning of what is ray tracing and how to achieve, from display a picture in ppm format to the realization of ray tracing, the tutorial is: [Ray Tracing in One Weekend](https://github.com/RayTracing/raytracing.github.io).

# Usage

    $ git clone https://github.com/IT-dreamer/Simple-RayTracer.git
    $ cd Simple-RayTracer
    $ mkdir build
    $ cd ./build
    $ cmake ..
    $ make
The cpp files in the src file correspond to different chapter exercises, just specify the `MAIN_FILE` in the CMakeLists.txt to the target file.

# How to check ppm file
You can use the [Web PPM Viewer](https://0xc0de.fr/webppm/).The ppm file are stored in the temp file. Because it's compiling with **/src/8_MetalMaterial.cpp**, you will see  
![](/doc/result.png)
