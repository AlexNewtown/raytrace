#define _USE_MATH_DEFINES
#include "Trace/IrradianceCache.hpp"

#include "Math/Vector.hpp"

#include <algorithm>

namespace Trace {

IrradianceCache::IrradianceCache()
{
	mOctree = std::make_unique<OctreeNode>();
	mOctreeOrigin = Math::Point(0, 0, 0);
	mOctreeSize = 20;
}

void IrradianceCache::setThreshold(float threshold)
{
	mThreshold = threshold;
}

float IrradianceCache::weight(const Entry &entry, const Math::Point &point, const Math::Normal &normal) const 
{
	//return std::pow(std::max(double(0), 1.0f - (point - entry.point).magnitude2() / (1.0 * entry.radius * std::pow(normal * entry.normal, 4.0f))), 2);
	return 1.0f / ((point - entry.point).magnitude() / entry.radius + std::sqrt(1 - normal * entry.normal));
}

float IrradianceCache::error(const Entry &entry, const Math::Point &point, const Math::Normal &normal) const
{
	return ((4.0f / M_PI) * (point - entry.point).magnitude() / entry.radius + std::sqrt(1 - normal * entry.normal));
}

void IrradianceCache::lookupOctreeNode(OctreeNode *node, Math::Point origin, float size, const Math::Point &point, const Math::Normal &normal, std::vector<Entry> &entries) const
{
	for (const Entry &e : node->entries)
	{
		float d = (point - e.point) * ((normal + e.normal) / 2);
		if (d >= -0.01 && weight(e, point, normal) > 1 / mThreshold)
		{
			entries.push_back(e);
		}
	}

	for (int i = 0; i < 8; i++) {
		float x = (i & 1) ? 1 : -1;
		float y = (i & 2) ? 1 : -1;
		float z = (i & 4) ? 1 : -1;

		float childSize = size / 2;
		Math::Point childOrigin = origin + Math::Vector(x, y, z) * childSize;

		float distance = 0;
		float d;
		if (point.x() < childOrigin.x() - childSize) { d = ((childOrigin.x() - childSize) - point.x()); distance += d * d; }
		if (point.y() < childOrigin.y() - childSize) { d = ((childOrigin.y() - childSize) - point.y()); distance += d * d; }
		if (point.z() < childOrigin.z() - childSize) { d = ((childOrigin.z() - childSize) - point.z()); distance += d * d; }
		if (point.x() > childOrigin.x() + childSize) { d = (point.x() - (childOrigin.x() + childSize)); distance += d * d; }
		if (point.y() > childOrigin.y() + childSize) { d = (point.y() - (childOrigin.y() + childSize)); distance += d * d; }
		if (point.z() > childOrigin.z() + childSize) { d = (point.z() - (childOrigin.z() + childSize)); distance += d * d; }
		distance = std::sqrt(distance);

		if (distance < childSize && node->children[i]) {
			lookupOctreeNode(node->children[i].get(), childOrigin, childSize, point, normal, entries);
		}
	}
}

std::vector<IrradianceCache::Entry> IrradianceCache::lookup(const Math::Point &point, const Math::Normal &normal) const
{
	std::vector<Entry> entries;
	std::lock_guard<std::mutex> guard(mMutex);

	lookupOctreeNode(mOctree.get(), mOctreeOrigin, mOctreeSize, point, normal, entries);

	return entries;
}

void IrradianceCache::add(const Entry &entry)
{
	std::lock_guard<std::mutex> guard(mMutex);

	float R = entry.radius * mThreshold;

	Math::Point origin = mOctreeOrigin;
	float size = mOctreeSize;
	OctreeNode *node = mOctree.get();
	while (true) {
		if (size > R * 2) {
			float x = (entry.point.x() > origin.x()) ? 1 : -1;
			float y = (entry.point.y() > origin.y()) ? 1 : -1;
			float z = (entry.point.z() > origin.z()) ? 1 : -1;

			int idx = ((x > 0) ? 1 : 0) + ((y > 0) ? 2 : 0) + ((z > 0) ? 4 : 0);
			Math::Point newOrigin = origin + Math::Vector(x, y, z) * size / 2;

			if (!node->children[idx])
			{
				node->children[idx] = std::make_unique<OctreeNode>();
			}

			origin = newOrigin;
			size /= 2;
			node = node->children[idx].get();
		} else {
			node->entries.push_back(entry);
			break;
		}
	}
}

void IrradianceCache::clear()
{
	mOctree = std::make_unique<OctreeNode>();
}

}