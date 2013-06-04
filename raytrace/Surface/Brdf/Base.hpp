#ifndef SURFACE_BRDF_BASE_HPP
#define SURFACE_BRDF_BASE_HPP

#include "Math/Forwards.hpp"

#include "Object/Color.hpp"

namespace Surface {
namespace Brdf {

class Base {
public:
	virtual ~Base() {}

	virtual Object::Color color(const Object::Color &incidentColor, const Math::Vector &incidentDirection, const Math::Normal &normal, const Math::Vector &outgoingDirection, const Object::Color &albedo) const = 0;

	static const Base *fromAst(AST *ast);
};

}
}

#endif