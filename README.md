# Raytracer
Under development!

Features:
- OBJ model loading
  * using tinyobjloader: https://github.com/syoyo/tinyobjloader
- BVH acceleration
- Simple Shading
- Uses YAML format for configuration and scenes

TODO:
- Implement scenes
- Image file writing (PNG/TIFF/Something)
- Materials
- Support for multiple objects
- SAH KDTree implementation instead of BVH
- (In the far future Realtime Raytracing with a scene editor; extend this task to smaller ones when this comes closer)

## Compiling instructions
The project is dependent on yaml-cpp. On OSX/Linux you need to install the `yaml-cpp` package first. On Windows the libraries are already included.
Generate the project with CMake and compile.

## Usage instructions
Non-BVH accelerated raytracing:
```
raytracer.exe obj_file_name.obj
```

With BVH acceleration:
```
raytracer.exe obj_file_name.obj -bvh
```

See the `example_config.yaml`
