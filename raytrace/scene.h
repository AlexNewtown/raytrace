#ifndef SCENE_H
#define SCENE_H

#include "camera.h"
#include "light.h"
#include "primitive.h"

#include "intersection.h"

#include "photon.h"

#include <vector>

class Scene
{
public:
	Scene(double aspectRatio);
	~Scene();

	Camera *camera() const;
	void setCamera(Camera *camera);

	const std::vector<Light*> &lights() const;
	void addLight(Light *light);

	const std::vector<Primitive*> &primitives() const;
	void addPrimitive(Primitive *primitive);

	void findIntersections(const Ray &ray, std::vector<Intersection> &intersections);

	void photonMap(int numPhotons);

	const PhotonMap &photonMap() const;

protected:
	Camera *mCamera;
	std::vector<Light*> mLights;
	std::vector<Primitive*> mPrimitives;
	double mAspectRatio;
	PhotonMap mPhotonMap;
};

#endif
