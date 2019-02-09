#pragma once

#define _USE_MATH_DEFINES
#include <math.h>


namespace MathClass
{
	float DegreesToRadians(float degree);
	float RadiansToDegrees(float radian);

	// constexpr = declares that it's possible to evaluate the value of this function at compile time
	static constexpr float oneDegreeInRadians = M_PI / 180.0f;
	static constexpr float oneRadianInDegrees = 180.0f / M_PI;
};
