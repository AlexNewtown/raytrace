#include "Render/Tracer.hpp"
#include "Object/Scene.hpp"
#include "Object/Camera.hpp"
#include "Object/Surface.hpp"

#include "Object/Brdf/Base.hpp"
#include "Object/Albedo/Base.hpp"
#include "Object/Primitive.hpp"

#include <algorithm>

namespace Render {

Tracer::Tracer(const Object::Scene &scene, int width, int height)
	: mScene(scene)
{
	mWidth = width;
	mHeight = height;
}

const Object::Scene &Tracer::scene() const
{
	return mScene;
}

Object::Intersection Tracer::intersect(const Math::Ray &ray)
{
	Object::Intersection intersection;
	Object::Primitive *primitive = 0;
	float distance = FLT_MAX;
	Math::Normal normal;

	Object::BoundingVolume::RayData rayData = Object::BoundingVolume::getRayData(ray);

	for (const std::unique_ptr<Object::Primitive> &testPrimitive : mScene.primitives())
	{
		float volumeDistance;
		if (testPrimitive->boundingVolume().intersectRay(rayData, volumeDistance) && volumeDistance < distance) {
			if(testPrimitive->shape().intersect(ray, distance, normal)) {
				primitive = testPrimitive.get();
			}
		}
	}

	if (distance < FLT_MAX) {
		return Object::Intersection(*primitive, ray, distance, normal);
	}
	else {
		return Object::Intersection();
	}
}

Math::Ray Tracer::createCameraRay(float x, float y)
{
	float cx = (2 * x - mWidth) / mWidth;
	float cy = (2 * y - mHeight) / mWidth;
	Math::Ray ray = mScene.camera().createRay(cx, -cy);

	return ray;
}

float Tracer::projectedPixelSize(float distance)
{
	return mScene.camera().projectSize(2.0f / mWidth, distance);
}

}