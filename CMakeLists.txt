cmake_minimum_required(VERSION 3.10)
set(project_name "raytracer")
project(${project_name})

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

file(GLOB SOURCE_FILES
    "src/main.cpp"
    "src/raytracer/*.cpp"
    "src/raytracer/*.h"
    "src/utils/tiny_obj_loader.h"
)

add_executable(${project_name} ${SOURCE_FILES})
set_target_properties(${project_name} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin/")

if(MSVC)
    set_property(TARGET ${project_name} PROPERTY CXX_STANDARD 17)
    set_property(TARGET ${project_name} PROPERTY CXX_STANDARD_REQUIRED ON)
else(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -O3")
    set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # For YouCompleteMe
endif(MSVC)
