#include "Object/Shape/Grid.hpp"
#include "Object/Shape/Triangle.hpp"

namespace Object {
	namespace Shape {
        Grid::Grid(unsigned int width, unsigned int height, std::vector<Vertex> &&vertices)
			: mWidth(width), mHeight(height), mVertices(std::move(vertices))
		{
			std::vector<Object::BoundingVolumeHierarchy::Node> nodes;
			nodes.reserve(mWidth * mHeight * 2);
			computeBounds(nodes, 0, 0, mWidth - 1, mHeight - 1);

			mBoundingVolumeHierarchy = Object::BoundingVolumeHierarchy(std::move(nodes));
		}

        unsigned int Grid::computeBounds(std::vector<Object::BoundingVolumeHierarchy::Node> &nodes, unsigned int uMin, unsigned int vMin, unsigned int uMax, unsigned int vMax) const
		{
			nodes.push_back(Object::BoundingVolumeHierarchy::Node());
            unsigned int nodeIndex = static_cast<unsigned int>(nodes.size() - 1);
			Object::BoundingVolumeHierarchy::Node &node = nodes[nodeIndex];

			if (uMax - uMin == 1 && vMax - vMin == 1) {
                node.index = -static_cast<int>(vMin * mWidth + uMin);
                for (unsigned int i = uMin; i <= uMax; i++) {
                    for (unsigned int j = vMin; j <= vMax; j++) {
						node.volume.expand(vertex(i, j).point);
					}
				}
			}
			else {
				if (uMax - uMin >= vMax - vMin) {
                    unsigned int uSplit = (uMin + uMax) / 2;
					computeBounds(nodes, uMin, vMin, uSplit, vMax);
					node.index = computeBounds(nodes, uSplit, vMin, uMax, vMax);
				}
				else {
                    unsigned int vSplit = (vMin + vMax) / 2;
					computeBounds(nodes, uMin, vMin, uMax, vSplit);
                    node.index = static_cast<int>(computeBounds(nodes, uMin, vSplit, uMax, vMax));
				}

				node.volume.expand(nodes[nodeIndex + 1].volume);
                node.volume.expand(nodes[static_cast<unsigned int>(node.index)].volume);
			}

            return nodeIndex;
		}

        const Grid::Vertex &Grid::vertex(unsigned int u, unsigned int v) const
		{
			return mVertices[v * mWidth + u];
		}

		bool Grid::intersect(const Math::Ray &ray, Intersection &intersection) const
		{
			BoundingVolume::RayData rayData = BoundingVolume::getRayData(ray);

            auto callback = [&](unsigned int index, float &) {
				bool ret = false;
                unsigned int u = index % mWidth;
                unsigned int v = index / mWidth;
				const Vertex &vertex0 = vertex(u, v);
                Math::Point2D surfacePoint0(static_cast<float>(u) / mWidth, static_cast<float>(v) / mHeight);
				const Vertex &vertex1 = vertex(u + 1, v);
                Math::Point2D surfacePoint1(static_cast<float>(u + 1) / mWidth, static_cast<float>(v) / mHeight);
				const Vertex &vertex2 = vertex(u, v + 1);
                Math::Point2D surfacePoint2(static_cast<float>(u)/ mWidth, static_cast<float>(v + 1) / mHeight);
				const Vertex &vertex3 = vertex(u + 1, v + 1);
                Math::Point2D surfacePoint3(static_cast<float>(u + 1) / mWidth, static_cast<float>(v + 1) / mHeight);

				float tu, tv;
				if (Triangle::intersect(ray, vertex0.point, vertex1.point, vertex2.point, intersection.distance, tu, tv)) {
					intersection.normal = vertex0.normal * (1 - tu - tv) + vertex1.normal * tu + vertex2.normal * tv;
					intersection.tangent = vertex0.tangent * (1 - tu - tv) + vertex1.tangent * tu + vertex2.tangent * tv;
					intersection.surfacePoint = surfacePoint0 * (1 - tu - tv) + surfacePoint1 * tu + surfacePoint2 * tv;
					ret = true;
				}
				if (Triangle::intersect(ray, vertex3.point, vertex2.point, vertex1.point, intersection.distance, tu, tv)) {
					intersection.normal = vertex3.normal * (1 - tu - tv) + vertex2.normal * tu + vertex1.normal * tv;
					intersection.tangent = vertex3.tangent * (1 - tu - tv) + vertex2.tangent * tu + vertex1.tangent * tv;
					intersection.surfacePoint = surfacePoint3 * (1 - tu - tv) + surfacePoint2 * tu + surfacePoint1 * tv;
					ret = true;
				}

				return ret;
			};

			return mBoundingVolumeHierarchy.intersect(rayData, intersection.distance, std::ref(callback));
		}

		BoundingVolume Grid::boundingVolume(const Math::Transformation &transformation) const
		{
			BoundingVolume volume;
			for (const Vertex &vertex : mVertices) {
				volume.expand(transformation * vertex.point);
			}

			return volume;
		}
	}
}
