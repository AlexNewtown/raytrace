#include "csg.h"

Csg::Csg()
{
}

Primitive *Csg::primitive1()
{
	return mPrimitive1;
}

void Csg::setPrimitive1(Primitive *primitive1)
{
	mPrimitive1 = primitive1;
}

Primitive *Csg::primitive2()
{
	return mPrimitive2;
}

void Csg::setPrimitive2(Primitive *primitive2)
{
	mPrimitive2 = primitive2;
}

Csg::Type Csg::type() const
{
	return mType;
}

void Csg::setType(Type type)
{
	mType = type;
}

bool Csg::doInside(const Vector &point) const
{
	switch(mType)
	{
	case TypeUnion:
		return mPrimitive1->inside(point) || mPrimitive2->inside(point);
	case TypeIntersection:
		return mPrimitive1->inside(point) && mPrimitive2->inside(point);
	case TypeDifference:
		return mPrimitive1->inside(point) && !mPrimitive2->inside(point);
	}

	return false;
}

void Csg::doIntersect(const Ray &ray, std::vector<Intersection> &intersections) const
{
	std::vector<Intersection> localIntersections;

	mPrimitive1->intersect(ray, localIntersections);
	mPrimitive2->intersect(ray, localIntersections);

	for(int i=0; i<localIntersections.size(); i++)
	{
		bool add = false;

		switch(mType)
		{
		case TypeUnion:
			if(localIntersections[i].primitive() == mPrimitive1 && !mPrimitive2->inside(localIntersections[i].point()) ||
			   localIntersections[i].primitive() == mPrimitive2 && !mPrimitive1->inside(localIntersections[i].point()))
			{
				add = true;
			}
			break;

		case TypeIntersection:
			if(localIntersections[i].primitive() == mPrimitive1 && mPrimitive2->inside(localIntersections[i].point()) ||
			   localIntersections[i].primitive() == mPrimitive2 && mPrimitive1->inside(localIntersections[i].point()))
			{
				add = true;
			}
			break;

		case TypeDifference:
			if(localIntersections[i].primitive() == mPrimitive1 && !mPrimitive2->inside(localIntersections[i].point()) ||
			   localIntersections[i].primitive() == mPrimitive2 && mPrimitive1->inside(localIntersections[i].point()))
			{
				add = true;
			}
			break;
		}

		if(add)
		{
			intersections.push_back(localIntersections[i]);
		}
	}
}