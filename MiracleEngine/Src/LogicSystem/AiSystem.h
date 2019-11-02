#pragma once
#include "PrecompiledHeaders.h"

#ifndef AISYSTEM_H
#define	AISYSTEM_H

class AiComponent; // forward decalre from AiComp, cause AiComp need to be accessed

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

	size_t _timeUpdateRate;	// how fast the AI system will update
	size_t _timeUpdatePrev; // previous 'time' updated
	size_t _timeUpdateElapsed; // currTime - _timeUpdatePrev

	// hard coded tilemap
	std::unordered_map < size_t, Node* > _tilemap;
	unsigned _mapTileSize = 10;
	unsigned _mapHeight = 10;
	unsigned _mapWidth = 10;

	//size_t _tilemapInput[5][5] =
	//{ // hardcoded 5x5 map that will be converted into an actual Node*
	//	{ 0,0,0,0,0 },
	//	{ 0,1,0,1,0 },
	//	{ 0,1,0,1,0 },
	//	{ 0,1,0,0,1 },
	//	{ 0,0,0,1,1 },
	//}; // 1 == solid

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

	size_t _tilemapInput[10][10] = {
		{ 0,0,0,0,1,0,0,0,0,0 },
		{ 1,0,0,1,0,0,0,0,0,0 },
		{ 1,0,0,1,0,1,0,0,0,0 },
		{ 1,0,0,1,0,1,0,0,0,0 },
		{ 1,0,0,0,0,1,0,0,0,0 },
		{ 0,1,0,1,0,1,0,0,0,0 },
		{ 0,0,0,1,0,1,0,0,0,0 },
		{ 0,1,1,1,0,1,0,0,0,0 },
		{ 0,0,1,0,0,1,0,0,0,0 },
		{ 0,0,0,0,1,0,0,0,0,0 },
	};

public:
	AISystem() = default;
	~AISystem() = default;
	AISystem(const AISystem& rhs) = delete;
	AISystem& operator=(const AISystem& rhs) = delete;

// GetSet
	size_t GetTimeUpdateRate();
	void SetTimeUpdate(size_t time);
	size_t GetTimeUpdatePrev();
	void SetTimePrev(size_t time);
	size_t GetTimeUpdateElapsed();
	void SetTimeElapsed(size_t time);
	std::unordered_map < size_t, Node* > GetTileMap();
	void SetTileMap(std::unordered_map < size_t, Node* > map);

// InUpEx
	void Init(std::unordered_map < size_t, Node* > map); // make sure GOFac serial gives the _tilemap
	void Update(size_t currTime);
	void Exit();

// Create a node map from _tilemap
	void CreateNodeMap(); // sets up _tilemap with Nodes with their UpDownLeftRight Node*

// PathFinding
	//std::vector<Node*> PathFinding(Vector3& _curr, Vector3& _dest);
	std::vector<Node*> PathFinding(); // testing, once done use line above

// FSM
	void FSM()
	{

	}
};

#endif
