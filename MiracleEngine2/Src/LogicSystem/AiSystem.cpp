#include "PrecompiledHeaders.h"
#include "AiSystem.h"

bool Node::GetSolid()
{
	return _solid;
}
size_t Node::GetNodeId()
{
	return _nodeId;
}
Vector3 Node::GetPosition()
{
	return _position;
}

void AISystem::Init()
{
}
void AISystem::Update(const std::unordered_map < size_t, AiComponent* >& aimap, size_t currTime)
{
	// update will occur only every ~0.5 seconds
	_timeUpdateElapsed = (currTime - _timeUpdatePrev);
	if (_timeUpdateElapsed < _timeUpdateRate)
		return;
	else // run AI
		_timeUpdatePrev = currTime;
	// run through map, run each AiComp->Update()
	for (auto const& x : aimap)
	{
		x.second->Update(_tilemap);
	}


	// run through BFS
}
void AISystem::Exit()
{
}