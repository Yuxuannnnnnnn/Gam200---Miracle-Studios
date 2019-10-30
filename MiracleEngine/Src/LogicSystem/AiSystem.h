#pragma once
#include "PrecompiledHeaders.h"

#ifndef AISYSTEM_H
#define	AISYSTEM_H

class AiComponent; // forward decalre from AiComp, cause we need to throw the map of AiComps

class Node {
private:
	bool _solid;
	size_t _nodeId;
	Vector3 _position;
public:
	bool GetSolid();
	size_t GetNodeId();
	Vector3 GetPosition();
};

class AISystem
{
private:
	size_t _timeUpdateRate;	// how fast the AI system will update
	size_t _timeUpdatePrev; // previous 'time' updated
	size_t _timeUpdateElapsed; // currTime - _timeUpdatePrev
	std::vector<Node> _tilemap; // all AiComps will access this map for pathfinding
public:
	AISystem();
// InUpEx
	void Init(); // make sure GOFac serial gives the _tilemap
	void Update(const std::unordered_map < size_t, AiComponent* >& aimap, size_t currTime);
	void Exit();
// PathFinding
	bool PathFinding(Vector3& _curr, Vector3& _dest, std::vector<Node*> _path)
	{
		// run pathfinding algorithm based on '_curr' toward '_dest'
			// A* (std use) or BFS(more expensive but easier)	
		// TODO: BFS Implementation
	}
// FSM
	void FSM()
	{

	}
};

#endif
