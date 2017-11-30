cmake_minimum_required(VERSION 3.6)
set(project_name "raytracer")
project(${project_name})

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

IF(NOT WIN32 OR NOT WIN64)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O3")
    set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # For YouCompleteMe
ENDIF(NOT WIN32 OR NOT WIN64)

file(GLOB SOURCE_FILES
    "src/main.cpp"
    "src/raytracer/*.cpp"
    "src/raytracer/*.h"
    "src/utils/tiny_obj_loader.h"
)

add_executable(${project_name} ${SOURCE_FILES})
set_target_properties(${project_name} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin/")
