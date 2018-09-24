#include "Trace/Tracer.hpp"
#include "Object/Base.hpp"
#include "Object/Scene.hpp"
#include "Object/Camera.hpp"
#include "Object/Surface.hpp"

#include "Object/Brdf/Base.hpp"
#include "Object/Albedo/Base.hpp"
#include "Object/Primitive/Base.hpp"

#include <algorithm>

namespace Trace {

Tracer::Tracer(const Object::Scene &scene, const Settings &settings)
	: mScene(scene)
{
	mSettings = settings;
}

const Object::Scene &Tracer::scene() const
{
	return mScene;
}

Tracer::Settings &Tracer::settings()
{
	return mSettings;
}

Trace::Intersection Tracer::intersect(const Trace::Ray &ray)
{
	Trace::Intersection intersection;

	for (const std::unique_ptr<Object::Primitive::Base> &primitive : mScene.primitives())
	{
		if (primitive->boundingVolume().intersectRay(ray)) {
			Trace::Intersection newIntersection = primitive->intersect(ray);
			if (!intersection.valid() || newIntersection.distance() < intersection.distance()) {
				intersection = newIntersection;
			}
		}
	}

	return intersection;
}

Trace::Ray Tracer::createCameraRay(float x, float y)
{
	float cx = (2 * x - mSettings.width) / mSettings.width;
	float cy = (2 * y - mSettings.height) / mSettings.width;
	Trace::Ray ray = mScene.camera().createRay(cx, cy, 1);

	return ray;
}

float Tracer::projectedPixelSize(float distance)
{
	return mScene.camera().projectSize(2.0f / mSettings.width, distance);
}

}