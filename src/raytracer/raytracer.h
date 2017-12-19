#ifndef RAYTRACER_H
#define RAYTRACER_H

#include <string>
#include <memory>

#include "bvhnode.h"
#include "ray.h"
#include "trianglemesh.h"

namespace Raytracer {
    class Raytracer {
    public:
        Raytracer();
        void Render();
        bool LoadModel(const std::string &filename);

        void SetBVH(bool isEnabled);
        void ReadConfig(const std::string &filename);

    private:
        bool TraceRay(const Ray &ray, TriangleMesh &mesh, float &tNear, bool &rayHit, Vec3f &normal);
        Vec3f GetColor(const Ray &ray, TriangleMesh &mesh);

        void WriteFile(const std::vector<Vec3f> &frameBuffer);

        TriangleMesh m_mesh;

        std::vector<Vec3f> m_imageBuffer;
        std::shared_ptr<BVHNode> m_bvh;

        Vec3f m_bgColor;
        Vec3f m_lookFrom;
        Vec3f m_lookAt;

        Vec3f m_hitColor;
        Vec3f m_normal;

        Vec3f m_lightPosition;
        Vec3f m_lightColor;

        float m_tNear;
        float m_infinity;
        float m_epsilon;

        float m_width;
        float m_height;

        bool m_useBVH;
        bool m_rayHit;
    };
}
#endif // !RAYTRACER_H
