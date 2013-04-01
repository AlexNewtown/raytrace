#ifndef SCENE_H
#define SCENE_H

#include "Object/Camera.hpp"
#include "Object/Light.hpp"
#include "Object/Primitive.hpp"

#include "intersection.h"

#include <vector>

namespace Object {

class Scene
{
public:
	Scene();
	~Scene();

	Camera *camera() const;
	void setCamera(Camera *camera);

	const std::vector<Light*> &lights() const;
	void addLight(Light *light);

	const std::vector<Primitive*> &primitives() const;
	void addPrimitive(Primitive *primitive);

	void findIntersections(const Math::Ray &ray, std::vector<Intersection> &intersections);

protected:
	Camera *mCamera;
	std::vector<Light*> mLights;
	std::vector<Primitive*> mPrimitives;
};

}
#endif
