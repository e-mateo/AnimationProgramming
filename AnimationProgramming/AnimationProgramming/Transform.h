#pragma once
#include "Maths.h"


struct Transform
{
public:
	Transform();

	maths::Vec3 pos;
	maths::Quat rot;
};