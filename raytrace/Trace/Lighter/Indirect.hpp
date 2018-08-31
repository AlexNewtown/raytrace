#ifndef TRACE_LIGHTER_INDIRECT_HPP
#define TRACE_LIGHTER_INDIRECT_HPP

#include "Trace/Lighter/Base.hpp"
#include "Trace/Lighter/Direct.hpp"

#include <random>

namespace Trace {
	namespace Lighter {

		class Indirect : public Base
		{
		public:
			Indirect(int indirectSamples, int indirectDirectSamples);

			virtual Object::Radiance light(const Trace::Intersection &intersection, Trace::Tracer &tracer) const;

		private:
			mutable std::default_random_engine mRandomEngine;
			int mIndirectSamples;
			Direct mDirectLighter;
		};

	}
}

#endif