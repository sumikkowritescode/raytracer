#include "bvhnode.h"
#include <limits>

namespace Raytracer {
    BVHNode::BVHNode() :
        m_infinity(std::numeric_limits<float>::max())
    {}

    std::shared_ptr<BVHNode> BVHNode::Build(const std::vector<std::shared_ptr<Triangle>> &triangles, int depth) {
        std::shared_ptr<BVHNode> node(new BVHNode());
        node->m_triangles = triangles;
        node->m_left = nullptr;
        node->m_right = nullptr;
        node->m_bbox = BoundingBox();

        if (triangles.size() == 0)
            return node;

        if (triangles.size() == 1)
        {
            node->m_bbox = triangles[0]->GetBoundingBox();
            node->m_left = std::make_shared<BVHNode>();
            node->m_right = std::make_shared<BVHNode>();
            node->m_left->m_triangles = std::vector<std::shared_ptr<Triangle>>();
            node->m_right->m_triangles = std::vector<std::shared_ptr<Triangle>>();
            return node;
        }

        // Get the whole bounding box for the triangles in this node
        node->m_bbox = triangles[0]->GetBoundingBox();

        for (size_t i = 1; i < triangles.size(); i++) {
            node->m_bbox.Expand(triangles[i]->GetBoundingBox());
        }

        // Divide the triangles into the two child-nodes based on the triangles' mid-point location on the split bounding box axis
        // Repeat until 50% of the triangles are matching on both child nodes
        Vec3f midPoint = Vec3f(0.0f, 0.0f, 0.0f);

        for (size_t i = 0; i < triangles.size(); i++) {
            midPoint = midPoint + (triangles[i]->GetMidPoint() * (1.0f / triangles.size()));
        }

        std::vector<std::shared_ptr<Triangle>> leftTriangles;
        std::vector<std::shared_ptr<Triangle>> rightTriangles;

        int axis = node->m_bbox.GetLongestAxis();

        for (size_t i = 0; i < triangles.size(); i++) {
            if (axis == 0)
                if (midPoint.x >= triangles[i]->GetMidPoint().x)
                    rightTriangles.push_back(triangles[i]);
                else
                    leftTriangles.push_back(triangles[i]);
            else if (axis == 1)
                if (midPoint.y >= triangles[i]->GetMidPoint().y)
                    rightTriangles.push_back(triangles[i]);
                else
                    leftTriangles.push_back(triangles[i]);
            else if (axis == 2)
                if (midPoint.z >= triangles[i]->GetMidPoint().z)
                    rightTriangles.push_back(triangles[i]);
                else
                    leftTriangles.push_back(triangles[i]);
        }

        if (leftTriangles.size() == 0 && rightTriangles.size() > 0)
            leftTriangles = rightTriangles;

        if (rightTriangles.size() == 0 && leftTriangles.size() > 0)
            rightTriangles = leftTriangles;

        int match = 0;
        for (size_t i = 0; i < leftTriangles.size(); i++) {
            for (size_t j = 0; j < rightTriangles.size(); j++) {
                if (leftTriangles[i] == rightTriangles[j])
                    match++;
            }
        }

        if ((float)match / leftTriangles.size() < 0.5f && (float)match / rightTriangles.size() < 0.5f) {
            node->m_left = Build(leftTriangles, depth + 1);
            node->m_right = Build(rightTriangles, depth + 1);
        }
        else
        {
            node->m_left = std::make_shared<BVHNode>();
            node->m_right = std::make_shared<BVHNode>();
            node->m_left->m_triangles = std::vector<std::shared_ptr<Triangle>>();
            node->m_right->m_triangles = std::vector<std::shared_ptr<Triangle>>();
        }

        return node;
    }

    // Recursively test if ray intersects a bounding box, at the leaf node do ray/triangle intersection
    bool BVHNode::GetIntersection(const std::shared_ptr<BVHNode> &node, const Ray &ray, float &tNear, Vec3f &normal) {
        if (node->m_bbox.GetIntersection(ray))
        {
            bool intersect = false;

            if (node->m_left->m_triangles.size() > 0 || node->m_right->m_triangles.size() > 0)
            {
                bool hitLeft = GetIntersection(node->m_left, ray, tNear, normal);
                bool hitRight = GetIntersection(node->m_right, ray, tNear, normal);
                return hitLeft || hitRight;
            }
            else
            {
                for (const auto &triangle : node->m_triangles)
                {
                    float t = m_infinity;

                    if (triangle->GetIntersection(ray, t) && t < tNear)
                    {
                        intersect = true;
                        tNear = t;
                        normal = triangle->GetNormal();
                    }
                }
                return intersect;
            }
        }
        return false;
    }
}
