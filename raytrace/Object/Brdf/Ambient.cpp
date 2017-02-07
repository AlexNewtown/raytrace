#include "Object/Brdf/Ambient.hpp"

#include "Parse/AST.h"

namespace Object {
namespace Brdf {

Ambient::Ambient(float strength)
{
	mStrength = strength;
}

Object::Radiance Ambient::radiance(const Object::Radiance &incidentRadiance, const Math::Vector &incidentDirection, const Math::Normal &normal, const Math::Vector &outgoingDirection, const Object::Color &albedo) const
{
	return incidentRadiance * albedo * mStrength;
}

std::unique_ptr<Ambient> Ambient::fromAst(AST *ast)
{
	return std::make_unique<Ambient>(ast->data._float);
}

}
}