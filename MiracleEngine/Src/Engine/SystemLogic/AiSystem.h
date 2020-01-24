#pragma once
#include <queue>

#ifndef AISYSTEM_H
#define	AISYSTEM_H

static bool displayDebug = false;

class GameObject;	// forward declare from GameObject, need TypeId::WALL
class AiComponent; // forward decalre from AiComp, cause AiComp need to be accessed

#define MAP_SIZE 100
#define MAP_HEIGHT 30
#define MAP_WIDTH 40

class Node {
private:
	bool _solid;	// to prevent usage of node
	bool _visited;	// use for BFS algorithm
	bool _closed; // Astar
	size_t _nodeId;
	Vector3 _position;	// position of Node in  World
// Node pointers
	Node* _PtrNodeUp;
	Node* _PtrNodeDown;
	Node* _PtrNodeLeft;
	Node* _PtrNodeRight;
	Node* _PtrNodePrev;
public:
	size_t _f, _g, _h; // size_t cause using Vector3.SquaredLength

	Node(bool solid, size_t id, Vector3 pos);
	void SetNodeAdjacent(Node* up, Node* down, Node* left, Node* right);
	bool GetSolid();
	size_t GetNodeId();
	Vector3 GetPosition();
	bool GetVisited();
	void SetVisited(bool in);
	bool GetClosed();
	void SetClosed(bool in);
	Node* GetLeft();
	Node* GetRight();
	Node* GetUp();
	Node* GetDown();
	Node* GetPrev();
	void SetPrev(Node* prev);

	void CalcFGH(Vector3 _start, Vector3 _dest); // A*
};

class AISystem
{
private:
	// all GO with AI components
	//std::unordered_map < size_t, AiComponent* >& _aimap; // get from factory

	bool init;

	double _timer{ 0 };
	double _timeCooldown{ 0.1 };

	// hard coded tilemap
	std::unordered_map < size_t, Node* > _tileNodeMap;
	size_t** _tilemapInput;
	size_t _mapHeight, _mapWidth, _mapTileSize;

public:
	AISystem();
	~AISystem() = default;
	AISystem(const AISystem& rhs) = delete;
	AISystem& operator=(const AISystem& rhs) = delete;

// GetSet
	void SetTimeElapsed(size_t time);
	std::unordered_map < size_t, Node* > GetTileMap();
	void SetTileMap(std::unordered_map < size_t, Node* > map);
	size_t GetMapTileSize();
	void SetInit();

// InUpEx
	void Init(); // make sure GOFac serial gives the _tilemap
	void Update(double dt);
	void Exit();

// Create a node map from _tilemap
	void CreateNodeMap(); // sets up _tilemap with Nodes with their UpDownLeftRight Node*
	void CreateNodeMapFromTileComp();

// PathFinding
	//std::vector<Node*> PathFinding(Vector3& _curr, Vector3& _dest);
	std::vector<Node*> PathFindingOld(Vector3 curr, Vector3 dest); // testing, once done use line above
	std::vector<Node*> PathFinding(Vector3 curr, Vector3 dest);
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


	"AllTileMaps": [{
			"TransformComponent": true,
			"Position": [ 0.0, 0.0 ],
			"Scale": [ 70.0, 70.0 ],
			"Rotate": 0.0,
			"TileMapComponent":  true,
			"Width": 16,
	  "Height": 15,
	  "TileSize": 100,
			"Palette": [
				[
					0,
					"Floor"
				],
				[
					1,
					"MapEdge"
				],
				[
					2,
					"Wall"
				],
				[
					3,
					"Spawner"
				],
				[
					4,
					"SpawnerTwo"
				]
			],
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
		}],


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
	],

	"NonClonableObjects": []
}
*/
