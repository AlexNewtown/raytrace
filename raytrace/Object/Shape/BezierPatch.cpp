#include "Object/Shape/BezierPatch.hpp"

namespace Object {
namespace Shape {

BezierPatch::BezierPatch(int width, int height, std::vector<Math::Point> &&controlPoints)
{
	std::vector<Math::Point> points;

	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++) {
			float s = float(i) / (width - 1);
			float t = float(j) / (height - 1);

			float Bs[4] = { (1 - s)*(1 - s)*(1 - s), 3 * s*(1 - s)*(1 - s), 3 * s*s*(1 - s), s*s*s };
			float Bt[4] = { (1 - t)*(1 - t)*(1 - t), 3 * t*(1 - t)*(1 - t), 3 * t*t*(1 - t), t*t*t };
			Math::Vector p;
			for (int k = 0; k < 4; k++) {
				for (int l = 0; l < 4; l++) {
					p = p + Math::Vector(controlPoints[k * 4 + l]) * (Bs[l] * Bt[k]);
				}
			}
			points.push_back(Math::Point(p));
		}
	}

	mGrid = std::make_unique<Grid>(width, height, std::move(points));
}

bool BezierPatch::intersect(const Math::Ray &ray, float &distance, Math::Normal &normal) const
{
	return mGrid->intersect(ray, distance, normal);
}

BoundingVolume BezierPatch::boundingVolume(const Math::Transformation &transformation) const
{
	return mGrid->boundingVolume(transformation);
}

bool BezierPatch::sample(float u, float v, Math::Point &point, Math::Vector &du, Math::Vector &dv, Math::Normal &normal) const
{
	return mGrid->sample(u, v, point, du, dv, normal);
}

}
}