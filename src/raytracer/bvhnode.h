#ifndef KDNODE_H
#define KDNODE_H

#include <vector>
#include <memory>
#include "trianglemesh.h"

namespace Raytracer {
    class BVHNode {
    public:
        BVHNode();

        std::shared_ptr<BVHNode> Build(const std::vector<std::shared_ptr<Triangle>> &triangles, int depth);
        bool GetIntersection(const std::shared_ptr<BVHNode> &node, const Ray &ray, float &tNear, Vec3f &normal);

    private:
        BoundingBox m_bbox;

        std::shared_ptr<BVHNode> m_left;
        std::shared_ptr<BVHNode> m_right;

        std::vector<std::shared_ptr<Triangle>> m_triangles;

        float m_infinity;
    };
}
#endif // !KDNODE_H
