#include "trianglemesh.h"

#include <vector>
#include <limits>
#include <algorithm>

static std::string GetBaseDir(const std::string &filepath) {
    if (filepath.find_last_of("/\\") != std::string::npos)
    return filepath.substr(0, filepath.find_last_of("/\\"));
return "";
}

namespace Raytracer {
    TriangleMesh::TriangleMesh() :
        m_infinity(std::numeric_limits<float>::max())
    {
    }

    bool TriangleMesh::GetIntersection(const Ray &ray, float &tNear, Vec3f &normal) {
        bool intersected = false;

        for (const auto &triangle : m_triangles) {
            float t = m_infinity;

            if (triangle->GetIntersection(ray, t) && t < tNear)
            {
                tNear = t;
                intersected = true;
                normal = triangle->GetNormal();
            }
        }
        return intersected;
    }

    bool TriangleMesh::LoadOBJFromFile(const char *filename) {
        std::string base_dir = GetBaseDir(filename);

        if (base_dir.empty()) {
            base_dir = ".";
        }

#ifdef _WIN32
    base_dir += "\\";
#else
    base_dir += "/";
#endif

        std::string err;
        std::vector<Vec3f> vertices;

        bool ret =
          tinyobj::LoadObj(&attrib, &shapes, &materials, &err, filename, base_dir.c_str());
        if (!err.empty()) {
            std::cerr << err << std::endl;
        }
    
        if (!ret) {
            std::cerr << "Failed to load " << filename << std::endl;
            return false;
        }

        std::cout << "Loaded model from OBJ file: " << filename << "\n" << std::endl;

        printf("vertices  = %d\n", (int)(attrib.vertices.size()) / 3);
        printf("normals   = %d\n", (int)(attrib.normals.size()) / 3);
        printf("texcoords = %d\n", (int)(attrib.texcoords.size()) / 2);
        printf("materials = %d\n", (int)materials.size());
        printf("shapes    = %d\n", (int)shapes.size());

        for (size_t i = 0; i < attrib.vertices.size(); i+=3)
            vertices.push_back(Vec3f(attrib.vertices[i], attrib.vertices[i+1], attrib.vertices[i+2]));

        m_bbox.Calculate(vertices);

        for(const auto &shape : shapes)
        {
            size_t indexOffset = 0;
            for (size_t f = 0; f < shape.mesh.num_face_vertices.size(); f++)
            {
                size_t fv = shape.mesh.num_face_vertices[f];
                for(size_t v = 0; v < fv; v++)
                {
                    const tinyobj::index_t &idx0 = shape.mesh.indices[indexOffset + 0]; // v0
                    const tinyobj::index_t &idx1 = shape.mesh.indices[indexOffset + 1]; // v1
                    const tinyobj::index_t &idx2 = shape.mesh.indices[indexOffset + 2]; // v2

                    if (attrib.normals.size() != 0)
                    {
                        m_triangles.push_back(std::make_shared<Triangle>(
                                Vec3f(attrib.vertices[3 * idx0.vertex_index + 0], attrib.vertices[3 * idx0.vertex_index + 1], attrib.vertices[3 * idx0.vertex_index + 2]),
                                Vec3f(attrib.vertices[3 * idx1.vertex_index + 0], attrib.vertices[3 * idx1.vertex_index + 1], attrib.vertices[3 * idx1.vertex_index + 2]),
                                Vec3f(attrib.vertices[3 * idx2.vertex_index + 0], attrib.vertices[3 * idx2.vertex_index + 1], attrib.vertices[3 * idx2.vertex_index + 2]),

                                Vec3f(attrib.normals[3 * idx0.normal_index + 0], attrib.normals[3 * idx0.normal_index + 1], attrib.normals[3 * idx0.normal_index + 2]),
                                Vec3f(attrib.normals[3 * idx1.normal_index + 0], attrib.normals[3 * idx1.normal_index + 1], attrib.normals[3 * idx1.normal_index + 2]),
                                Vec3f(attrib.normals[3 * idx2.normal_index + 0], attrib.normals[3 * idx2.normal_index + 1], attrib.normals[3 * idx2.normal_index + 2])
                            ));
                    }
                    else
                    {
                        m_triangles.push_back(std::make_shared<Triangle>(
                                Vec3f(attrib.vertices[3 * idx0.vertex_index + 0], attrib.vertices[3 * idx0.vertex_index + 1], attrib.vertices[3 * idx0.vertex_index + 2]),
                                Vec3f(attrib.vertices[3 * idx1.vertex_index + 0], attrib.vertices[3 * idx1.vertex_index + 1], attrib.vertices[3 * idx1.vertex_index + 2]),
                                Vec3f(attrib.vertices[3 * idx2.vertex_index + 0], attrib.vertices[3 * idx2.vertex_index + 1], attrib.vertices[3 * idx2.vertex_index + 2])
                        ));
                    }
                }
                indexOffset += fv;
            }
        }

        return true;
    }

    BoundingBox TriangleMesh::GetBoundingBox() const {
        return m_bbox;
    }

    std::vector<std::shared_ptr<Triangle>> &TriangleMesh::GetTriangles() {
        return m_triangles;
    }
}
