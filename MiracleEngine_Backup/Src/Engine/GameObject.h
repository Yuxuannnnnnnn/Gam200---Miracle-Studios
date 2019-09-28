#pragma once
#include "MathLib/Vector3.h"
#include <vector>
#include "Inputsystem/inputsystem.h"
#include "Tools/FileIO.h"

enum GameObjectType {
	UNKOWN = 0,
	PLAYER,
	WALL,
	FLOOR,
	MISC,
};

struct TempGO {
	int id{ 0 };
	Vector3 pos{ Vector3() };
	Vector3 scale{ Vector3() };
	float rot{ 0.0f };
	TempGO() {}
	~TempGO() {}
};

struct GameObject
{
	int _id{ UNKOWN };

	GameObject(Vector3 pos = Vector3{ 0,0 }, Vector3 scale = Vector3{ 20,20 }, float angle = 0) :
		_pos{pos}, _scale{scale}, _angle{angle}
	{
	}
	virtual ~GameObject() = default;
	Vector3 _pos{ Vector3() };
	Vector3 _scale{ Vector3() };
	float _angle{ 0.0f };

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
	~Wall() {}

	void Update() override
	{}

	Wall* Clone(Vector3 pos, Vector3 scale, float rotate) override;
};

struct Floor : public GameObject {
	Floor()
	{
		_id = FLOOR;
	}
	~Floor() {}

	void Update() override
	{}

	Floor* Clone(Vector3 pos, Vector3 scale, float rotate) override;
};

struct Player : public GameObject {
	InputSystem keyboard;
	int _Health{ 0 };
	float _Speed{ 0.0f };
	std::vector<int> _WeaponListId;

	Player() 
	{
		_id = PLAYER;
	}
	~Player() {}

	virtual void Update()
	{
		keyboard.Update();
		Movement();
	}
	Player* Clone(Vector3 pos, Vector3 scale, float rotate) override;


	void Serialize()
	{
		std::cout << "FileRead_PlayerInfo -----------------" << std::endl;
		rapidjson::Document d;
		char* iBuffer = FileRead_FileToCharPtr("./Resources/TextFiles/player.json");
		std::cout << iBuffer << std::endl;
		ASSERT(iBuffer != nullptr);
		d.Parse<rapidjson::kParseStopWhenDoneFlag>(iBuffer);
		// get values from the Document;

		rapidjson::Value& s = d["Health"];
		JsonDynamicStore(_Health, s);

		s = d["Speed"];
		JsonDynamicStore(_Speed, s);

		s = d["Weapons"];
		JsonDynamicStore(_WeaponListId, s);

		s = d["Position"];
		JsonDynamicStore(_pos, s);

		s = d["Scale"];
		JsonDynamicStore(_scale, s);

		s = d["Rotate"];
		JsonDynamicStore(_angle, s);

		std::cout << "-------------------------------------" << std::endl;

		delete[] iBuffer;
	}

	void Movement()
	{
		Vector3 move;
		// based on key pressed, move player
		if (keyboard.KeyDown(KEYB_UP))
			move.Y(1);
		if (keyboard.KeyDown(KEYB_DOWN))
			move.Y(-1);
		if (keyboard.KeyDown(KEYB_RIGHT))
			move.X(1);
		if (keyboard.KeyDown(KEYB_LEFT))
			move.X(-1);
		if (keyboard.KeyDown(KEYB_O))
			_angle+=3;
		if (keyboard.KeyDown(KEYB_P))
			_angle -= 3;
		_pos += move;
	}
	
};

std::vector<GameObject*> FileRead_Level(const char* FileName);

extern std::vector<GameObject*> objList;
extern std::map <std::string, GameObject*> objFab;