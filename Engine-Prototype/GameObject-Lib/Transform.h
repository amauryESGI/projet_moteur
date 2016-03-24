#pragma once

#include "helper.h"

class Transform
{
public:
	Transform() : Position(0.0f, 0.0f, 0.0f), Rotation(0.0f, 0.0f, 0.0f), Scale(1.0f, 1.0f, 1.0f) {}

	Vec3 Position;
	Vec3 Rotation;
	Vec3 Scale;

	~Transform() {}
};