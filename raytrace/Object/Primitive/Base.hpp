#ifndef OBJECT_PRIMITIVE_BASE_HPP
#define OBJECT_PRIMITIVE_BASE_HPP

#include "Object/Base.hpp"
#include "Surface/Base.hpp"
#include "Trace/Intersection.hpp"
#include "Trace/Ray.hpp"
#include "Math/Point.hpp"

#include <vector>

namespace Object {
namespace Primitive {

class Base : public Object::Base
{
public:
	Base();
	virtual ~Base();

	static Base *fromAst(AST *ast);

	Surface::Base *surface() const;
	void setSurface(Surface::Base *surface);

	void intersect(const Trace::Ray &ray, std::vector<Trace::Intersection> &intersections) const;
	bool inside(const Math::Point &point) const;

protected:
	Surface::Base *mSurface;

	virtual void doIntersect(const Trace::Ray &ray, Trace::IntersectionVector &intersections) const = 0;
	virtual bool doInside(const Math::Point &point) const = 0;
};

}
}

#endif