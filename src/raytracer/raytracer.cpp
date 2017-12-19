#include <algorithm>
#include <vector>
#include <fstream>
#include <chrono>
#include <limits>
#include <cassert>
#include <sstream>

#include "camera.h"
#include "raytracer.h"

namespace Raytracer {
    Raytracer::Raytracer() :
        m_infinity(std::numeric_limits<float>::max()),
        m_epsilon(1e-8),
        m_bgColor(Vec3f(0.0f, 0.0f, 0.0f)),
        m_lightPosition(Vec3f(0.5f, 0.2f, 0.6f)),
        m_lightColor(Vec3f(1.0f, 1.0f, 1.0f))
    {
    }

    bool Raytracer::TraceRay(const Ray &ray, TriangleMesh &mesh, float &tNear, bool &rayHit, Vec3f &normal) {
        float tNearTriangle = m_infinity;
        if (!m_useBVH)
        {
            if (mesh.GetIntersection(ray, tNearTriangle, normal) && tNearTriangle < tNear) {
                rayHit = true;
                tNear = tNearTriangle;
            }
            return rayHit;
        }
        else if (m_useBVH)
        {
            if (m_bvh->GetIntersection(m_bvh, ray, tNearTriangle, normal) && tNearTriangle < tNear)
            {
                rayHit = true;
                tNear = tNearTriangle;
            }
            return rayHit;
        }
        return rayHit;
    }

    Vec3f Raytracer::GetColor(const Ray &ray, TriangleMesh &mesh) {
        m_hitColor = m_bgColor;
        m_tNear = m_infinity;
        m_rayHit = false;

        if (TraceRay(ray, mesh, m_tNear, m_rayHit, m_normal)) {
            float cosTheta = std::clamp(dot(m_normal, m_lightPosition), 0.0f, 1.0f);
            m_hitColor = cosTheta * m_lightColor;
        }
        return m_hitColor;
    }

    void Raytracer::Render() {
        auto startTime = std::chrono::high_resolution_clock::now();

        Camera cam(m_lookFrom, m_lookAt, Vec3f(0.0f, -1.0f, 0.0f), 50.0f, float(m_width) / float(m_height));

        // The ray tracing loop
        for (int j = 0; j < m_height; ++j) {
            for (int i = 0; i < m_width; ++i) {
                float u = float(i) / float(m_width);
                float v = float(j) / float(m_height);
                Ray r = cam.GetRay(u, v);

                m_imageBuffer.push_back(GetColor(r, m_mesh));
            }
        }

        auto endTime = std::chrono::high_resolution_clock::now();
        auto elapsedTime = std::chrono::duration<double, std::milli>(endTime - startTime).count();
        fprintf(stderr, "\rDone: %.2f seconds \n", elapsedTime / 1000);

        WriteFile(m_imageBuffer);
    }

    bool Raytracer::LoadModel(const std::string &filename) {
        bool loaded = false;

        if (m_mesh.LoadOBJFromFile(filename.c_str()))
            loaded = true;

        if (m_useBVH && loaded)
            m_bvh = m_bvh->Build(m_mesh.GetTriangles(), 0);

        return loaded;
    }

    void Raytracer::SetBVH(bool isEnabled) {
        m_useBVH = isEnabled;
    }

    void Raytracer::WriteFile(const std::vector<Vec3f> &frameBuffer) {
        const int frame = 0;
        char buffer[256];

        sprintf(buffer, "out.%04d.ppm", frame);
        std::ofstream ofs;

        ofs.open(buffer);
        ofs << "P6\n" << m_width << " " << m_height << "\n255\n";

        for (uint32_t i = 0; i < m_height * m_width; ++i)
        {
            char r = (char)(255 * frameBuffer[i].x);
            char g = (char)(255 * frameBuffer[i].y);
            char b = (char)(255 * frameBuffer[i].z);
            ofs << r << g << b;
        }
    }

    void Raytracer::ReadConfig(const std::string &filename) {
        std::ifstream configFile;
        configFile.open(filename, std::ios_base::in);
        assert(configFile.is_open());

        for(std::string line; std::getline(configFile, line); )
        {
            std::istringstream in(line);

            std::string type;
            in >> type;

            if (type == "width")
            {
                int width;
                in >> width;
                m_width = static_cast<float>(width);
            }
            else if (type == "height")
            {
                int height;
                in >> height;
                m_height = static_cast<float>(height);
            }
            else if(type == "origin")
            {
                float x, y, z;
                in >> x >> y >> z;
                m_lookFrom = Vec3f(x, y, z);
            }
            else if(type == "target")
            {
                float x, y, z;
                in >> x >> y >> z;
                m_lookAt = Vec3f(x, y, z);
            }
        }
        configFile.close();
        std::cout << "Width: " << m_width << " x " << m_height << std::endl;;
        std::cout << "Camera origin: " << m_lookFrom << std::endl;
        std::cout << "Camera target: " << m_lookAt << "\n" << std::endl;
    }
}
