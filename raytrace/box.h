#ifndef BOX_H
#define BOX_H

#include "primitive.h"

class Box : public Primitive
{
public:
	Box();

protected:
	virtual void doIntersect(const Ray &ray, std::vector<Intersection> &intersections) const;
	virtual bool doInside(const Vector &point) const;

	void testIntersect(const Ray &ray, const Vector &normal, std::vector<Intersection> &intersections) const;
};

#endif
