#ifndef OBJECT_PRIMITIVE_BOUNDING_VOLUME_HPP
#define OBJECT_PRIMITIVE_BOUNDING_VOLUME_HPP

#include "Math/Vector.hpp"
#include "Trace/Ray.hpp"

#include <vector>

namespace Object {
namespace Primitive {

class BoundingVolume
{
public:
	struct RayData {
		std::vector<float> offsets;
		std::vector<float> invdots;
	};

	BoundingVolume() = default;
	BoundingVolume(const std::vector<float> &mins, const std::vector<float> &maxes);

	BoundingVolume translate(const Math::Vector &translate);

	bool intersectRay(const RayData &rayData) const;

	static const std::vector<Math::Vector> &vectors();
	static RayData getRayData(const Trace::Ray& ray);

private:
	std::vector<float> mMins;
	std::vector<float> mMaxes;
};

}
}
#endif