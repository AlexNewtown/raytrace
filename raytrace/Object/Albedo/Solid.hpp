#ifndef OBJECT_ALBEDO_SOLID_HPP
#define OBJECT_ALBEDO_SOLID_HPP

#include "Object/Albedo/Base.hpp"

namespace Object {
	namespace Albedo {
		class Solid : public Base
		{
		public:
			Solid(const Object::Color &color);

			virtual Object::Color color(float u, float v) const;

		protected:
			Object::Color mColor;
		};
	}
}
#endif