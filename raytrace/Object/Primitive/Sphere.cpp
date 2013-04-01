#include "Object/Primitive/Sphere.hpp"
#include "Math/Transformation.hpp"

#include <math.h>

#define EPSILON 0.0001

namespace Object {
namespace Primitive {

Sphere::Sphere()
{
}

Sphere *Sphere::fromAst(AST *ast)
{
	return new Sphere();
}

void Sphere::doIntersect(const Math::Ray &ray, std::vector<Trace::Intersection> &intersections) const
{
	Trace::Intersection intersection;
	double a, b, c;
	double disc;

	a = ray.direction().magnitude2();
	b = 2 * (ray.origin().vector() * ray.direction());
	c = ray.origin().vector().magnitude2() - 1;

	disc = b * b - 4 * a * c;
	if(disc >= 0)
	{
		double distance = (-b - sqrt(disc)) / (2 * a);

		if(distance > EPSILON)
		{
			Math::Point point = ray.origin() + ray.direction() * distance;
			intersections.push_back(Trace::Intersection(this, distance, point.vector(), point));
		}

		distance = (-b + sqrt(disc)) / (2 * a);

		if(distance > EPSILON)
		{
			Math::Point point = ray.origin() + ray.direction() * distance;
			intersections.push_back(Trace::Intersection(this, distance, point.vector(), point));
		}
	}
}

bool Sphere::doInside(const Math::Point &point) const
{
	return point.vector().magnitude2() <= 1;
}

}
}