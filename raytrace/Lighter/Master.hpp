#ifndef LIGHTER_MASTER_HPP
#define LIGHTER_MASTER_HPP

#include "Lighter/Base.hpp"

#include <memory>
#include <vector>

namespace Lighter {

class Master : public Base
{
public:
	struct Settings {
		bool radiantLighting;
		bool specularLighting;
		bool directLighting;
		int directSamples;
		bool indirectLighting;
		int indirectSamples;
		int indirectDirectSamples;
		bool irradianceCaching;
		float irradianceCacheThreshold;
		int maxRayGeneration;
	};

	Master(const Settings &settings);

	virtual Object::Radiance light(const Object::Intersection &intersection, Render::Tracer &tracer, Probe *probe = 0) const;
	virtual bool prerender(const Object::Intersection &intersection, Render::Tracer &tracer) const;

private:
	std::vector<std::unique_ptr<Lighter::Base>> mLighters;
};

}
#endif