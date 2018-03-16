#include <algorithm>
#include <vector>
#include <fstream>
#include <chrono>
#include <limits>
#include <cassert>
#include <sstream>
#include <iomanip>

#include "camera.h"
#include "raytracer.h"
#include "yaml-cpp/yaml.h"

namespace Raytracer {
    Raytracer::Raytracer() :
        m_infinity(std::numeric_limits<float>::max()),
        m_epsilon(static_cast<float>(1e-8)),
        m_bgColor(Vec3f(0.0f, 0.0f, 0.0f)),
        m_lookFrom(Vec3f(0.0f, 0.0f, 1.0f)),
        m_lookAt(Vec3f(0.0f, 0.0f, 0.0f)),
        m_lightPosition(Vec3f(0.5f, 0.2f, 0.6f)),
        m_lightColor(Vec3f(1.0f, 1.0f, 1.0f)),
        m_width(640.0f),
        m_height(480.0f),
        m_useBVH(true)
    {
    }

    bool Raytracer::TraceRay(const Ray &ray, TriangleMesh &mesh, float &tNear, bool &rayHit, Vec3f &normal) {
        float tNearTriangle = m_infinity;

        // Use BVH always from now on.  Add more options once KDTree has been added.
        if (m_bvh->GetIntersection(m_bvh, ray, tNearTriangle, normal) && tNearTriangle < tNear)
        {
            rayHit = true;
            tNear = tNearTriangle;
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

        WriteFile(m_imageBuffer);

        auto endTime = std::chrono::high_resolution_clock::now();
        auto elapsedTime = std::chrono::duration<double, std::milli>(endTime - startTime).count();

        std::cout << "Done: " << std::setw(5) << elapsedTime/ 1000 << " seconds" << std::endl;
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

    // TODO: Repalce this with an image file writer instead
    void Raytracer::WriteFile(const std::vector<Vec3f> &frameBuffer) {
        std::ofstream imgFileStream;

        imgFileStream.open("image.ppm");
        imgFileStream << "P6\n" << m_width << " " << m_height << "\n255\n";

        for (size_t i = 0; i < m_height * m_width; ++i)
        {
            char r = (char)(255 * frameBuffer[i].x);
            char g = (char)(255 * frameBuffer[i].y);
            char b = (char)(255 * frameBuffer[i].z);
            imgFileStream << r << g << b;
        }

        imgFileStream.close();
    }

    void Raytracer::ReadConfig(const std::string &filename) {
        YAML::Node config = YAML::LoadFile(filename);

        m_width = config["settings"]["width"].as<float>();
        m_height = config["settings"]["height"].as<float>();

        m_lookFrom = Vec3f(config["settings"]["origin"][0].as<float>(),
                           config["settings"]["origin"][1].as<float>(),
                           config["settings"]["origin"][2].as<float>()
                          );
        m_lookAt   = Vec3f(config["settings"]["target"][0].as<float>(),
                           config["settings"]["target"][1].as<float>(),
                           config["settings"]["target"][2].as<float>()
                          );

        std::cout << "Width: " << m_width << " x " << m_height << std::endl;;
        std::cout << "Camera origin: " << m_lookFrom << std::endl;
        std::cout << "Camera target: " << m_lookAt << "\n" << std::endl;
    }
}
