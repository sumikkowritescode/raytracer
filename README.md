# Raytracer
Under development!

Features:
- OBJ model loading
  * using tinyobjloader: https://github.com/syoyo/tinyobjloader
- BVH acceleration
- Simple Shading

TODO:
- Implement YAML support for scenes
- Image file writing (PNG/TIFF/Something)
- Materials
- Support for multiple objects
- SAH KDTree implementation instead of BVH
- (In the far future Realtime Raytracing with a scene editor; extend this task to smaller ones when this comes closer)

## Compiling instructions
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

Camera settings and resolution can be changed in the `config` file in the format
e.g.
```
width 640 
height 480
origin x y z
target x y z
```
