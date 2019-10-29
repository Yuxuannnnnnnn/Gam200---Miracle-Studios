#pragma once
#include "PrecompiledHeaders.h"

struct Node {
	bool _solid;
	size_t _nodeId;

};

class AISystem
{
public:
	void Init()
	{}
	void Update(size_t time)
	{
		// update will occur only every ~0.5 seconds
		// run through BFS
	}
	void Exit()
	{}
};