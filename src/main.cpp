#define TINYOBJLOADER_IMPLEMENTATION 
#include "raytracer/raytracer.h"

#include <regex>
#include <string>

int main(int argc,  char* argv[]) {
    std::string filename;
    std::string bvh;

    bool useBVH = false;

    Raytracer::Raytracer raytracer;

    if (argc < 2 || argc > 3)
    {
        std::cout << "Usage: raytracer.exe obj_file_name.obj\n" << std::endl;
        std::cout << "To enable BVH acceleration, use the bvh flag: " << std::endl;
        std::cout << "raytracer.exe obj_file_name.obj -bvh\n" << std::endl;
        return 1;
    }
    else if (argc == 2)
        filename = argv[1];
    else if (argc == 3)
    {
        filename = argv[1];
        bvh = argv[2];
    }

    if (bvh == "-bvh")
        useBVH = true;

    raytracer.SetBVH(useBVH);

    std::regex objFileRegex("[a-zA-Z_0-9]+\\.obj");

    if(std::regex_match(filename, objFileRegex))
    {
        if (!useBVH)
            std::cout << "BVH not in use.\n" << std::endl;
        else if (useBVH)
            std::cout << "BVH in use.\n" << std::endl;

        // TODO: Read config from command line arguments
        raytracer.ReadConfig("config.yaml");

        if (raytracer.LoadModel(filename))
            raytracer.Render();
        else
            std::cout << "Failed to load model: " << filename << std::endl;
    }
    else
        std::cout << "Not an OBJ model file\n" << std::endl;

    return 0;
}
