#ifndef LIGHTER_BASE_HPP
#define LIGHTER_BASE_HPP

#include "Render/Tracer.hpp"

#include <vector>
#include <memory>

#include "Math/Vector.hpp"
#include "Object/Radiance.hpp"

namespace Lighter {

class Base;

class Base {
public:
	Base();

	struct Probe {
		struct Entry {
			Math::Vector direction;
			Object::Radiance radiance;
		};

		std::vector<Entry> entries;
	};

	virtual Object::Radiance light(const Object::Intersection &intersection, Render::Tracer &tracer) const = 0;
	virtual bool prerender(const Object::Intersection &intersection, Render::Tracer &tracer);

	void enableProbe(bool enabled);
	const Probe &probe() const;

protected:
	void clearProbe() const;
	void addProbeEntry(const Math::Vector &direction, const Object::Radiance &radiance) const;

private:
	std::unique_ptr<Probe> mProbe;
};

}

#endif