#ifndef OBJECT_ALBEDO_BASE_HPP
#define OBJECT_ALBEDO_BASE_HPP

#include "Object/Color.hpp"

#include "Math/Point2D.hpp"

namespace Object {
	namespace Albedo {
		class Base
		{
		public:
			virtual Object::Color color(const Math::Point2D &surfacePoint) const = 0;
		};
	}
}

#endif