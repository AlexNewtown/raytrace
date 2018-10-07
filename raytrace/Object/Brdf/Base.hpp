#ifndef OBJECT_BRDF_BASE_HPP
#define OBJECT_BRDF_BASE_HPP

#include "Object/Radiance.hpp"
#include "Object/Color.hpp"

#include "Math/Vector.hpp"
#include "Math/Normal.hpp"

#include <memory>

namespace Object {
namespace Brdf {

class Base {
public:
	virtual Object::Radiance diffuseRadiance(const Object::Radiance &incidentRadiance, const Math::Vector &incidentDirection, const Math::Normal &normal, const Math::Vector &outgoingDirection, const Object::Color &albedo) const;

	virtual bool specular() const;
	virtual Object::Radiance specularRadiance(const Object::Radiance &incidentRadiance, const Object::Color &albedo) const;

	virtual float lambert() const;

	static std::unique_ptr<Base> fromAst(AST *ast);
};

}
}

#endif