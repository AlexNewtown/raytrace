#ifndef LIGHTER_RADIANT_HPP
#define LIGHTER_RADIANT_HPP

#include "Lighter/Base.hpp"

namespace Lighter {

class Radiant : public Base
{
public:
	virtual Object::Radiance light(const Object::Intersection &intersection, Render::Tracer &tracer, Probe *probe = 0) const;
};

}

#endif