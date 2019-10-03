// temporary gameobject for testing, delete later
#include "GameObject.h"
#include <map>
#include <vector>
#include <string>

std::vector<GameObject*> objList;
std::vector<GameObject*> objStressTestList;
std::map <std::string, GameObject*> objFab;

Wall* Wall::Clone(Vector3 pos, Vector3 scale, float rotate)
{
	Wall* original = dynamic_cast<Wall*>(objFab["Wall"]);
	Wall* temp = new Wall();
	temp->_pos = pos;
	temp->_scale = scale;
	temp->_angle = rotate;
	temp->_id = original->_id;
	return temp;
}

Floor* Floor::Clone(Vector3 pos, Vector3 scale, float rotate)
{
	Floor* original = dynamic_cast<Floor*>(objFab["Floor"]);
	Floor* temp = new Floor();
	temp->_pos = pos;
	temp->_scale = scale;
	temp->_angle = rotate;
	temp->_id = original->_id;
	return temp;
}

Player* Player::Clone(Vector3 pos, Vector3 scale, float rotate)
{
	Player* original = dynamic_cast<Player*>(objFab["Player"]);
	Player* temp = new Player();
	temp->_pos = pos;
	temp->_scale = scale;
	temp->_angle = rotate;
	temp->_id = original->_id;
	temp->_Health = original->_Health;
	temp->_Speed = original->_Speed;
	temp->_WeaponListId = original->_WeaponListId;
	return temp;
}

std::vector<GameObject*> FileRead_Level(const char* FileName)
{ // will move to ObjectFactory
	std::fstream _file;
	_file.open(FileName, std::ios_base::in | std::ios_base::binary);
	if (!_file.is_open())
	{
		std::cout << "! WARNING !! File Cannot Open!!!" << std::endl
			<< ". // Resources // TextFiles // TestLevel.txt" << std::endl;
		std::vector<GameObject*> null;
		return null;
	}
	char* strType = new char[20];
	char* strNum1 = new char[10];
	char* strNum2 = new char[10];
	std::vector<TempGO> GOVec;
	float num1, num2;
	TempGO obj;

	while (_file.good()) // each loop read 4 lines: Type, Pos, Scale, Rot
	{
		// get Type
		//_file.getline(strType, 20, '\n\r');
		_file >> strType;
		if (std::strcmp(strType, "Wall") == 0)
			obj.id = WALL;
		if (std::strcmp(strType, "Floor") == 0)
			obj.id = FLOOR;
		if (std::strcmp(strType, "Player") == 0)
			obj.id = PLAYER;
		// get Position
		_file.getline(strNum1, 10, ',');
		_file.getline(strNum2, 10);
		num1 = std::stof(strNum1);
		num2 = std::stof(strNum2);
		obj.pos = Vector3(num1, num2, 1);
		// get Scale
		_file.getline(strNum1, 10, ',');
		_file.getline(strNum2, 10);
		num1 = std::stof(strNum1);
		num2 = std::stof(strNum2);
		obj.scale = Vector3(num1, num2, 1);
		// get Rotate
		_file.getline(strNum1, 10);
		num1 = std::stof(strNum1);
		obj.rot = num1;
		// push into tempVec
		GOVec.push_back(obj);
	}
	_file.close();
	delete[] strType;
	delete[] strNum1;
	delete[] strNum2;

	// instantiate objs into objList
	std::vector<GameObject*> ret;
	std::vector<TempGO>::iterator itr = GOVec.begin();
	while (itr != GOVec.end())
	{
		TempGO temp = *itr;
		if (temp.id == PLAYER)
			ret.push_back(objFab["Player"]->Clone(temp.pos,temp.scale,temp.rot));
		else if (temp.id == FLOOR)
			ret.push_back(objFab["Floor"]->Clone(temp.pos, temp.scale, temp.rot));
		else if (temp.id == WALL)
			ret.push_back(objFab["Wall"]->Clone(temp.pos, temp.scale, temp.rot));
		else;
		++itr;
	}
	return ret;
}