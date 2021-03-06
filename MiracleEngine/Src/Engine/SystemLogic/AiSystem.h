#pragma once
#include <queue>

#ifndef AISYSTEM_H
#define	AISYSTEM_H

static bool displayDebug = false;

class GameObject;	// forward declare from GameObject, need TypeId::WALL
//class AiComponent; // forward decalre from AiComp, cause AiComp need to be accessed
class Node;

//#define MAP_SIZE 100
//#define MAP_HEIGHT 30
//#define MAP_WIDTH 40


class AISystem
{
private:
	bool _init;
	double _timer, _timeCooldown;
	GameObject* NodeMapGO;
	size_t NodeMapGOId;
private: // copy of values taken from NodeMapGO
	Vector3 _mapTileSize;
	int _mapHeight,_mapWidth;
	int** _tilemapId;
	std::unordered_map < int, Node* > _tileNodeMap;
public:
	AISystem();
	~AISystem() = default;
	AISystem(const AISystem& rhs) = delete;
	AISystem& operator=(const AISystem& rhs) = delete;

// InUpEx
	void Init(); // make sure GOFac serial gives the _tilemap
	void Update(double dt);
	void Exit();

// PathFinding
	void UpdateNodeMapGO(); // call this when NodeMap is changed
	std::vector<Node*> PathFinding(Vector3 curr, Vector3 dest); // GO will call this function

	//std::vector<Node*> PathFinding(Vector3& _curr, Vector3& _dest);
	std::vector<Node*> PathFindingOld(Vector3 curr, Vector3 dest); // testing, once done use line above
};

#endif

/*
{
	"PrototypesFilePaths": [
		"./Resources/TextFiles/GameObjects/Wall.json",
		"./Resources/TextFiles/GameObjects/Floor.json",
		"./Resources/TextFiles/GameObjects/player.json",
		"./Resources/TextFiles/GameObjects/Enemy.json",
		"./Resources/TextFiles/GameObjects/Camera.json",
		"./Resources/TextFiles/GameObjects/Bullet.json",
		"./Resources/TextFiles/GameObjects/BulletE.json",
		"./Resources/TextFiles/GameObjects/BulletT.json",
		"./Resources/TextFiles/GameObjects/Turret.json",
		"./Resources/TextFiles/GameObjects/Spawner.json",
		"./Resources/TextFiles/GameObjects/SpawnerTwo.json",
		"./Resources/TextFiles/GameObjects/Font.json",
		"./Resources/TextFiles/GameObjects/TileMap.json",
		"./Resources/TextFiles/GameObjects/UiTest.json"
	],

	"TexturesFilesPaths": [
		"./Resources/Image/background.png"
	],

	"AnimationDataFilesPaths": [
		"./Resources/TextFiles/AnimationData/DatafileExplosionBluePlasma24FPSSprite.json"
	],

	"AudioFilesPaths": [
		"./Resources/Audio/Level1.ogg"
	],

	"ShaderFilesPaths": [
		"./Resources/Shader/basic.frag",
		"./Resources/Shader/basic.vert"
	],

	"FontFilesPath": [
		"./arial.ttf"
	],





	"ClonableObjects": [
		{
			"IdentityComponent": true,
			"ObjectType": "player"
		},
		{
			"IdentityComponent": true,
			"ObjectType": "Camera"
		},
		{
			"IdentityComponent": true,
			"ObjectType": "UiTest"
		}
		{
			"IdentityComponent": true,
			"ObjectType": "TileMapComponent"

			"TransformComponent": true,
			"Position": [ 0.0, 0.0 ],
			"Scale": [ 70.0, 70.0 ],
			"Rotate": 0.0,

			 "TileMapComponent":  true,
			 "Width": 16,
			 "Height": 15,
					"TileMap": [
							1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
							1, 3, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 3, 1,
							1, 4, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1,
							1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
							1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
							1, 0, 0, 0, 2, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 1,
							1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
							1, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
							1, 0, 0, 0, 2, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 1,
							1, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
							1, 2, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
							1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
							1, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 1,
							1, 3, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 4, 3, 1,
							1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
						]
				}
		}
	],

	"NonClonableObjects": []
}
*/
