#include "Surface/Albedo/Base.hpp"

#include "Surface/Albedo/Solid.hpp"
#include "Surface/Albedo/Checker.hpp"

#include "Parse/AST.h"

namespace Surface {
namespace Albedo {

Base::Base()
{
}

Base::~Base()
{
}

const Base *Base::fromAst(AST *ast)
{
	AST *albedoAst = ast->children[0];
	switch(albedoAst->type)
	{
	case AstAlbedoSolid:
		return Solid::fromAst(albedoAst);
	case AstAlbedoChecker:
		return Checker::fromAst(albedoAst);
	}

	return 0;
}

}
}