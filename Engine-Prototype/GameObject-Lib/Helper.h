#pragma once

struct Mat4
{

};

class RenderDataBinder
{
public:
	RenderDataBinder() {}

	Mat4 ViewMatrix;
	Mat4 ProjectionMatrix;
	Mat4 WorldMatrix;

	int NumberLight;

	~RenderDataBinder() {}
};

struct Vec3
{
	float x;
	float y;
	float z;

	Vec3() {}
	Vec3(float iX, float iY, float iZ) : x(iX), y(iY), z(iZ) {}
};