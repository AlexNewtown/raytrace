#ifndef OBJECT_SURFACE_HPP
#define OBJECT_SURFACE_HPP

#include "Object/Albedo/Base.hpp"
#include "Object/Brdf/Composite.hpp"

#include "Object/Color.hpp"
#include "Object/Radiance.hpp"
#include "Object/NormalMap.hpp"

#include <memory>

namespace Object {
	class Surface
	{
	public:
		Surface(std::unique_ptr<Albedo::Base> albedo, std::unique_ptr<Brdf::Composite> brdf, const Object::Radiance &radiance, std::unique_ptr<Object::NormalMap> normalMap);

		const Albedo::Base &albedo() const;
		const Brdf::Composite &brdf() const;
		const Object::Radiance &radiance() const;
		bool hasNormalMap() const;
		const Object::NormalMap &normalMap() const;

	private:
		std::unique_ptr<Albedo::Base> mAlbedo;
		std::unique_ptr<Brdf::Composite> mBrdf;
		Object::Radiance mRadiance;
		std::unique_ptr<Object::NormalMap> mNormalMap;
	};
}

#endif