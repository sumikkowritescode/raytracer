#define TINYOBJLOADER_IMPLEMENTATION 
#include "raytracer/raytracer.h"

#include <regex>
#include <string>

int main(int argc,  char* argv[]) {
    std::string filename;

    Raytracer::Raytracer raytracer;

    if (argc != 2)
    {
        std::cout << "Usage: raytracer.exe obj_file_name.obj\n" << std::endl;
        return 1;
    }
    else
        filename = argv[1];

    std::regex objFileRegex("[a-zA-Z_0-9]+\\.obj");

    if(std::regex_match(filename, objFileRegex))
    {
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
