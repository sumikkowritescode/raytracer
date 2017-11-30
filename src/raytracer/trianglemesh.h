#ifndef TRIANGLEMESH_H
#define TRIANGLEMESH_H
#include <memory>

#include "triangle.h"
#include "ray.h"
#include "bbox.h"

#include "../utils/tiny_obj_loader.h"

namespace Raytracer {
    class TriangleMesh {
    public:
        TriangleMesh();
        bool GetIntersection(const Ray &ray, float &tNear, Vec3f &normal);
        bool LoadOBJFromFile(const char *filename);

        BoundingBox GetBoundingBox() const;

        std::vector<std::shared_ptr<Triangle>> &GetTriangles();

    private:
        BoundingBox m_bbox;

        std::vector<std::shared_ptr<Triangle>> m_triangles;

        std::vector<tinyobj::shape_t> shapes;
        std::vector<tinyobj::material_t> materials;
        tinyobj::attrib_t attrib;

        float m_infinity;
    };
}

#endif // !TRIANGLEMESH_H
