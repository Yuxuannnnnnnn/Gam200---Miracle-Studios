#pragma once

// temporary gameobject for testing, delete later
#include <vector>

struct Vec3
{
	Vec3(float x, float y, float z = 1.0f)
		: _x{x}, _y{y}, _z{z}
	{
	}
	float _x;
	float _y;
	float _z;
};

struct GameObject
{
	GameObject(Vec3 pos = Vec3{ 0,0 }, Vec3 scale = Vec3{ 20,20 }, float angle = 0) :
		_pos{pos}, _scale{scale}, _angle{angle}
	{

	}
	Vec3 _pos;
	Vec3 _scale;
	float _angle;
	// TODO:: add more
};

extern std::vector<GameObject> objList;