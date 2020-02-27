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
	int _nodeId;
	Vector3 _position;	// position of Node in  World
// Node pointers
	Node* _PtrNodeUp;
	Node* _PtrNodeDown;
	Node* _PtrNodeLeft;
	Node* _PtrNodeRight;
	Node* _PtrNodePrev;
public:
	GameObject* _NodeObj;

	size_t _f, _g, _h; // size_t cause using Vector3.SquaredLength

	Node(bool solid, int id, Vector3 pos);
	~Node();
	void SetNodeAdjacent(Node* up, Node* down, Node* left, Node* right);
	bool GetSolid();
	void SetSolid(bool in);
	int GetNodeId();
	Vector3 GetPosition();
	void SetPosition(Vector3 pos);
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
	bool init;

	double _timer, _timeCooldown;

	int _mapHeight, _mapWidth, _mapTileSize;
	std::unordered_map < int, Node* > _tileNodeMap; // <NodeId, NodePtr>
	int** _tilemapInput; // 2dArray of the NodeMap in ID form

public:
	void SerialiseComponent(Serialiser& document);
	void DeSerialiseComponent(DeSerialiser& prototypeDoc);
	void DeSerialiseComponent(rapidjson::Value& prototypeDoc, rapidjson::MemoryPoolAllocator<>& allocator);
	void DeserialiseComponentSceneFile(IComponent* protoCom, rapidjson::Value& value, rapidjson::MemoryPoolAllocator<>& allocator);
	void Inspect();

	AISystem();
	~AISystem() = default;
	AISystem(const AISystem& rhs) = delete;
	AISystem& operator=(const AISystem& rhs) = delete;

// GetSet
	std::unordered_map < int, Node* > GetTileMap();
	void SetTileMap(std::unordered_map < int, Node* > map);
	int GetMapTileSize();
	void SetInit();

// InUpEx
	void Init(); // make sure GOFac serial gives the _tilemap
	void Update(double dt);
	void Exit();

// Create a node map from _tilemap
	void CreateNodeMap(int w, int h, int sz);
	void SetNodeMapOffset(int x, int y);

	void CreateNodeMap(); // sets up _tilemap with Nodes with their UpDownLeftRight Node*
	void CreateNodeMapFromTileComp();
	void ToggleNodeSolidity(float x, float y); // when picked a Node, call this function
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
