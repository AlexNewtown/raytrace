#ifndef LIGHTER_DIFFUSE_INDIRECT_HPP
#define LIGHTER_DIFFUSE_INDIRECT_HPP

#include "Lighter/Base.hpp"
#include "Lighter/Direct.hpp"
#include "Lighter/IrradianceCache.hpp"

#include <random>

namespace Lighter {
	class DiffuseIndirect : public Base
	{
	public:
		DiffuseIndirect(int indirectSamples, int indirectDirectSamples, bool irradianceCaching, float irradianceCacheThreshold);

		virtual Object::Radiance light(const Object::Intersection &intersection, Render::Sampler &sampler, int generation) const;
		virtual std::vector<std::unique_ptr<Render::Job>> createPrerenderJobs(const Object::Scene &scene, Render::Framebuffer &framebuffer);

	private:
		void prerenderPixel(int x, int y, Render::Framebuffer &framebuffer, const Object::Scene &scene, Render::Sampler &sampler);

		mutable std::default_random_engine mRandomEngine;
		int mIndirectSamples;
		bool mIrradianceCaching;
		Direct mDirectLighter;
		IrradianceCache mIrradianceCache;
	};
}

#endif