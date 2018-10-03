#ifndef OBJECT_PRIMITIVE_BASE_HPP
#define OBJECT_PRIMITIVE_BASE_HPP

#include "Object/Base.hpp"
#include "Object/Surface.hpp"
#include "Object/Intersection.hpp"
#include "Object/Primitive/BoundingVolume.hpp"

#include <vector>
#include <memory>

namespace Object {
namespace Primitive {

class Base : public Object::Base
{
public:
	static std::unique_ptr<Base> fromAst(AST *ast);

	const Surface &surface() const;
	void setSurface(std::unique_ptr<Surface> &&surface);

	Intersection intersect(const Math::Ray &ray) const;
	bool inside(const Math::Point &point) const;

	const BoundingVolume &boundingVolume() const;

protected:
	void computeBoundingVolume();

	static void parseAstCommon(Base &base, AST *ast);

	std::unique_ptr<Surface> mSurface;
	BoundingVolume mBoundingVolume;

	virtual Intersection doIntersect(const Math::Ray &ray) const = 0;
	virtual bool doInside(const Math::Point &point) const = 0;
	virtual BoundingVolume doBoundingVolume() const = 0;
};

}
}

#endif