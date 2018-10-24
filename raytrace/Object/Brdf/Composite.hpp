#ifndef OBJECT_BRDF_COMPOSITE_HPP
#define OBJECT_BRDF_COMPOSITE_HPP

#include "Object/Brdf/Base.hpp"

#include <vector>

namespace Object {
	namespace Brdf {
		class Composite
		{
		public:
			Composite(std::unique_ptr<Base> diffuse, std::unique_ptr<Base> specular, float transmitIor);

			bool hasDiffuse() const;
			const Base &diffuse() const;

			bool hasSpecular() const;
			const Base &specular() const;

			bool hasTransmit() const;
			float transmitIor() const;

		private:
			std::unique_ptr<Base> mDiffuse;
			std::unique_ptr<Base> mSpecular;
			float mTransmitIor;
		};
	}
}

#endif