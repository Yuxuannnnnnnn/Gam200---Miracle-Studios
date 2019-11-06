#pragma once
#include "PrecompiledHeaders.h"
#include <queue>

#ifndef AISYSTEM_H
#define	AISYSTEM_H

class GameObject;	// forward declare from GameObject, need TypeId::WALL
class AiComponent; // forward decalre from AiComp, cause AiComp need to be accessed

#define MAP_SIZE 100
#define MAP_HEIGHT 14
#define MAP_WIDTH 14

class Node {
private:
	bool _solid;	// to prevent usage of node
	bool _visited;	// use for BFS algorithm
	size_t _nodeId;
	Vector3 _position;	// position of Node in  World
// Node pointers
	Node* _PtrNodeUp;
	Node* _PtrNodeDown;
	Node* _PtrNodeLeft;
	Node* _PtrNodeRight;
	Node* _PtrNodePrev;
public:
	Node(bool solid, size_t id, Vector3 pos);
	void SetNodeAdjacent(Node* up, Node* down, Node* left, Node* right);
	bool GetSolid();
	size_t GetNodeId();
	Vector3 GetPosition();
	bool GetVisited();
	void SetVisited(bool in);
	Node* GetLeft();
	Node* GetRight();
	Node* GetUp();
	Node* GetDown();
	Node* GetPrev();
	void SetPrev(Node* prev);
};

class AISystem
{
private:
	// all GO with AI components
	//std::unordered_map < size_t, AiComponent* >& _aimap; // get from factory

	bool init;

	double _timer{ 0 };
	double _timeCooldown{ 2 };

	// hard coded tilemap
	std::unordered_map < size_t, Node* > _tilemap;
	int _mapTileSize = MAP_SIZE;
	int _mapHeight = MAP_HEIGHT;
	int _mapWidth = MAP_WIDTH;

	//size_t _tilemapInput[10][10] = {
	//	{ 0,0,0,0,0,0,0,0,0,0 },
	//	{ 0,0,0,0,0,0,0,0,0,0 },
	//	{ 0,0,0,0,0,0,0,0,0,0 },
	//	{ 0,0,0,0,0,0,0,0,0,0 },
	//	{ 0,0,0,0,0,0,0,0,0,0 },
	//	{ 0,0,0,0,0,0,0,0,0,0 },
	//	{ 0,0,0,0,0,0,0,0,0,0 },
	//	{ 0,0,0,0,0,0,0,0,0,0 },
	//	{ 0,0,0,0,0,0,0,0,0,0 },
	//	{ 0,0,0,0,0,0,0,0,0,0 },
	//};

	size_t _tilemapInput[MAP_HEIGHT][MAP_WIDTH] = {
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,2,0,0,0,0,2,0,0,0,2,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,1,1,1,1,1,1,1,1,1,1,0,1,0 },
		{ 0,1,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,1,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,1,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,1,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,1,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,3,0,3,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	};

public:
	AISystem();
	~AISystem() = default;
	AISystem(const AISystem& rhs) = delete;
	AISystem& operator=(const AISystem& rhs) = delete;

// GetSet
	void SetTimeElapsed(size_t time);
	std::unordered_map < size_t, Node* > GetTileMap();
	void SetTileMap(std::unordered_map < size_t, Node* > map);
	unsigned GetMapTileSize();
	void SetInit();

// InUpEx
	void Init(); // make sure GOFac serial gives the _tilemap
	void Update(double dt);
	void Exit();

// Create a node map from _tilemap
	void CreateNodeMap(); // sets up _tilemap with Nodes with their UpDownLeftRight Node*

// PathFinding
	//std::vector<Node*> PathFinding(Vector3& _curr, Vector3& _dest);
	std::vector<Node*> PathFinding(Vector3 curr, Vector3 dest); // testing, once done use line above
};

#endif