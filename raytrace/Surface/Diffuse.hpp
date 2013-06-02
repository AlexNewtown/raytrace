#ifndef SURFACE_DIFFUSE_HPP
#define SURFACE_DIFFUSE_HPP

#include "Surface/Base.hpp"

#include "Surface/Albedo/Forwards.hpp"

namespace Surface {

class Diffuse : public Base
{
public:
	Diffuse(Albedo::Base *albedo, float ambient, float lambert, float specular, float specularPower);
	virtual ~Diffuse();

	static Diffuse *fromAst(AST *ast);

	virtual Object::Color color(const Trace::Intersection &intersection, Trace::Tracer &tracer) const;

private:
	Albedo::Base *mAlbedo;
	float mAmbient;
	float mLambert;
	float mSpecular;
	float mSpecularPower;
};

}

#endif