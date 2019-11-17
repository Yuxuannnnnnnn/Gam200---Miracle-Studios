#pragma once
#include "MathLib/SYMath.h"
#include <vector>
#include <string>
#include "Inputsystem/inputsystem.h"
#include "Tools/FileIO.h"
#include "Engine/MemoryManager.h"


extern InputSystem* inputsystem;


enum GameObjectType {
	UNKOWN = 0,
	PLAYER,
	WALL,
	FLOOR,
	MISC,
};

struct GameObject
{
	int _id{ UNKOWN };

	GameObject(Vector3 pos = Vector3{ 0,0 }, Vector3 scale = Vector3{ 20,20 }, float angle = 0, const std::string& name = "zombie", bool isanimated = false) :
		_pos{pos}, _scale{scale}, _angle{angle}, _name{name}, _isAnimated{isanimated}
	{
	}
	virtual ~GameObject() = default;
	Vector3 _pos{ Vector3() };
	Vector3 _scale{ Vector3(1.f,1.f,1.f) };
	float _angle{ 0.0f };
	std::string _name;
	bool _isAnimated;

	virtual void Update() {
		std::cout << "A !" << std::endl;
	};
	virtual GameObject* Clone(Vector3 pos, Vector3 scale, float rotate)
	{
		return new GameObject();
	}


	
};

struct Wall : public GameObject {
	Wall()
	{
		_id = WALL;
	}
	~Wall()
	{
	}

	void Update() override
	{}

	Wall* Clone(Vector3 pos, Vector3 scale, float rotate) override;
};

struct Floor : public GameObject {
	Floor()
	{
		_id = FLOOR;
	}
	~Floor()
	{
	}

	void Update() override
	{}

	Floor* Clone(Vector3 pos, Vector3 scale, float rotate) override;
};



std::vector<GameObject*> FileRead_Level(const char* FileName);

extern std::vector<GameObject*> objList;
extern std::vector<GameObject*> objStressTestList;
extern std::map <std::string, GameObject*> objFab;