#include "Object/Radiance.hpp"
#include "Object/Color.hpp"

#include "Parse/AST.h"

namespace Object {

	Radiance::Radiance()
	{
		mRed = 0;
		mGreen = 0;
		mBlue = 0;
	}

	Radiance::Radiance(float red, float green, float blue)
	{
		mRed = red;
		mGreen = green;
		mBlue = blue;
	}

	Radiance::Radiance(const ASTVector &vector)
	{
		mRed = vector.x;
		mGreen = vector.y;
		mBlue = vector.z;
	}

	Radiance::Radiance(const Radiance &c)
	{
		mRed = c.mRed;
		mGreen = c.mGreen;
		mBlue = c.mBlue;
	}

	Radiance &Radiance::operator=(const Radiance &c)
	{
		mRed = c.mRed;
		mGreen = c.mGreen;
		mBlue = c.mBlue;

		return *this;
	}

	float Radiance::red() const
	{
		return mRed;
	}

	float Radiance::green() const
	{
		return mGreen;
	}

	float Radiance::blue() const
	{
		return mBlue;
	}

	Radiance Radiance::operator+(const Radiance &b) const
	{
		return Radiance(mRed + b.mRed, mGreen + b.mGreen, mBlue + b.mBlue);
	}

	Radiance &Radiance::operator+=(const Radiance &b)
	{
		mRed += b.mRed;
		mGreen += b.mGreen;
		mBlue += b.mBlue;

		return *this;
	}

	Radiance Radiance::operator/(float b) const
	{
		return Radiance(mRed / b, mGreen / b, mBlue / b);
	}

	Radiance Radiance::operator*(const Radiance &b) const
	{
		return Radiance(mRed * b.mRed, mGreen * b.mGreen, mBlue * b.mBlue);
	}

	Radiance Radiance::operator*(float b) const
	{
		return Radiance(mRed * b, mGreen * b, mBlue * b);
	}

	Radiance Radiance::operator*(const Color &b) const
	{
		return Radiance(mRed * b.red(), mGreen * b.green(), mBlue * b.blue());
	}
}