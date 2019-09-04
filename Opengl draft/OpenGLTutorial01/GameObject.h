#pragma once
struct Vec2
{
	float _x;
	float _y;
};

struct AABB
{
	Vec2	min;
	Vec2	max;
};

struct Color
{
	float _r;
	float _g;
	float _b;
};

enum TYPE
{
	PLAYER,
	BULLET,
	ENEMY
};

class GameObject
{
public:
	GameObject(float scale, Vec2 pos, Vec2 vel, float direc, Color color)
		: _scale{scale}, _posCurr{pos}, _velCurr{vel}, _dirCurr{direc}, _color{color}
	{
		
	}
public:
	float _scale;
	Vec2 _posCurr;
	Vec2 _velCurr;
	float _dirCurr;
	Color _color;
	AABB _boundingbox;
	TYPE _type;
};

class Player : public GameObject
{
public:
	Player(float scale, Vec2 pos, Vec2 vel, float direc, Color color)
		: GameObject(scale, pos, vel, direc, color)
	{

	}

};

class Bullet : public GameObject
{
public:
	Bullet(float scale, Vec2 pos, Vec2 vel, float direc, Color color)
		: GameObject(scale, pos, vel, direc, color)
	{

	}
};

class Enemy : public GameObject
{
public:
	Enemy(float scale, Vec2 pos, Vec2 vel, float direc, Color color)
		: GameObject(scale, pos, vel, direc, color)
	{

	}
};