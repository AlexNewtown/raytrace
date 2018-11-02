#ifndef OBJECT_NORMAL_MAP_HPP
#define OBJECT_NORMAL_MAP_HPP

#include "Object/Texture.hpp"

#include "Math/Vector.hpp"
#include "Math/Normal.hpp"
#include "Math/Point2D.hpp"
#include "Math/Bivector.hpp"

#include <memory>

namespace Object {
	class NormalMap
	{
	public:
		NormalMap(std::unique_ptr<Object::Texture<3>> texture, float magnitude);

		Math::Normal perturbNormal(const Math::Point2D &surfacePoint, const Math::Bivector2D &surfaceProjection, const Math::Normal &normal, const Math::Bivector &tangent) const;

	private:
		std::unique_ptr<Object::Texture<3>> mTexture;
		float mMagnitude;
	};
}
#endif