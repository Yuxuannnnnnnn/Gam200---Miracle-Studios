#include "PrecompiledHeaders.h"
#include "AiSystem.h"

/////////////////////////
// NODE stuff

Node::Node(bool solid, size_t id, Vector3 pos):
	_solid{ solid },
	_nodeId{ id },
	_position{pos}
{}

void Node::SetNodeAdjacent(Node* up, Node* down, Node* left, Node* right)
{
	_PtrNodeUp = up;
	_PtrNodeDown = down;
	_PtrNodeLeft = left;
	_PtrNodeRight = right;
}

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
bool Node::GetVisited()
{
	return _visited;
}
void Node::SetVisited(bool in)
{
	_visited = in;
}
Node* Node::GetLeft()
{
	return _PtrNodeLeft;
}
Node* Node::GetRight()
{
	return _PtrNodeRight;
}
Node* Node::GetUp()
{
	return _PtrNodeUp;
}
Node* Node::GetDown()
{
	return _PtrNodeDown;
}
Node* Node::GetPrev()
{
	return _PtrNodePrev;
}
void Node::SetPrev(Node* prev)
{
	_PtrNodePrev = prev;
}


// NODE stuff
/////////////////////////

/////////////////////////
// AISystem stuff

// GetSet
size_t AISystem::GetTimeUpdateRate()
{
	return _timeUpdateRate;
}
void AISystem::SetTimeUpdate(size_t time)
{
	_timeUpdateRate = time;
}
size_t AISystem::GetTimeUpdatePrev()
{
	return _timeUpdatePrev;
}
void AISystem::SetTimePrev(size_t time)
{
	_timeUpdatePrev = time;
}
size_t AISystem::GetTimeUpdateElapsed()
{
	return _timeUpdateElapsed;
}
void AISystem::SetTimeElapsed(size_t time)
{
	_timeUpdateElapsed = time;
}
std::unordered_map < size_t, Node* > AISystem::GetTileMap()
{
	return _tilemap;
}
void AISystem::SetTileMap(std::unordered_map < size_t, Node* > map)
{
	_tilemap = map;
}

// InUpEx
void AISystem::Init(std::unordered_map < size_t, Node* > map)
{
	SetTileMap(map);
}
void AISystem::Update(size_t currTime)
{
	// update will occur only every ~0.5 seconds
	_timeUpdateElapsed = (currTime - _timeUpdatePrev);
	if (_timeUpdateElapsed < _timeUpdateRate)
		return;
	else // run AI
		_timeUpdatePrev = currTime;
	// run through map, run each AiComp->Update()
		//for (auto const& x : _aimap)
		//{
		//	x.second->Update();
		//}


	// run through BFS
}
void AISystem::Exit()
{
}

void AISystem::CreateNodeMap()
{
	size_t id = 0; // id for Node's id
	Node* tempNode = nullptr;
	bool solid = false;
	Vector3 tempVecOrigin = Vector3(_mapTileSize/2, _mapTileSize / 2, 0);
	Vector3 tempVec;
	for (int i = 0; i < _mapHeight; ++i)
	{
		for (int j = 0; j < _mapWidth; ++j)
		{
		// Update tempVec
			tempVec = Vector3(
				tempVecOrigin._x + (j * _mapTileSize), // map grows rightwards
				tempVecOrigin._y - (i * _mapTileSize), // map grows downwards
				0);
		// Create node
			solid = _tilemapInput[i][j] == 1 ? true : false;
			tempNode = new Node(solid, id, tempVec );
				//_tilemap[id] = tempNode;
			_tilemap.insert(std::pair<size_t, Node*>(id, tempNode));
		// Assign id to the current _tilemap[][]
			_tilemapInput[i][j] = id++; //increment the id
		}
	}

	size_t currNode = 0;
	Node * up, * down, * left, * right;
	// link the Node's updownleftfight
	for (int i = 0; i < _mapHeight; ++i)
		for (int j = 0; j < _mapWidth; ++j)
		{
			currNode = _tilemapInput[i][j];
		// Left
			if (j > 0)
			{
				id = _tilemapInput[i][j - 1]; // add left ptr
				left = _tilemap[id];
				//std::cout << "L " << id << " ";
			}
			else
				left = nullptr; // put nullptr
		// Right
			if (j < _mapWidth-1)
			{
				id = _tilemapInput[i][j + 1];
				right = _tilemap[id];
				//std::cout << "R " << id << " ";
			}
			else
				right = nullptr;
		// Up
			if (i > 0)
			{
				id = _tilemapInput[i - 1][j];
				up = _tilemap[id];
				//std::cout << "U " << id << " ";
			}
			else
				up = nullptr;
		// Down
			if (i < _mapHeight-1)
			{
				id = _tilemapInput[i + 1][j];
				down = _tilemap[id];
				//std::cout << "D " << id << " ";
			}
			else
				down = nullptr;
		// Set Adjacent Nodes
			//std::cout << std::endl;
			_tilemap[currNode]->SetNodeAdjacent(up, down, left, right);
		}
	// Print the _tilemapInput
	for (int i = 0; i < _mapHeight; ++i)
	{
		for (int j = 0; j < _mapWidth; ++j)
		{
			std::cout << _tilemapInput[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

//std::vector<Node*> AISystem::PathFinding(Vector3& _curr, Vector3& _dest)
std::vector<Node*> AISystem::PathFinding()
{
	std::queue<Node*> listVisited;
	unsigned x, y;
	size_t nodeIdStart, nodeIdDest;
	std::vector<Node*> tempVec, finalVec;
// start node, end node // based on closest postiion, set the start(obj.pos()) and end (target.pos())
		// formula ( (x % _mapTileSize) + _mapTileSize/2 )
	//x = (((unsigned)_curr._x % _mapTileSize) + _mapTileSize / 2);
	//y = (((unsigned)_curr._y % _mapTileSize) + _mapTileSize / 2);
	//nodeIdStart = _tilemapInput[y][x];
	//x = (((unsigned)_dest._x % _mapTileSize) + _mapTileSize / 2);
	//y = (((unsigned)_dest._y % _mapTileSize) + _mapTileSize / 2);
	//nodeIdDest = _tilemapInput[y][x];
// fake start end nodes
	nodeIdStart = _tilemapInput[0][0];
	nodeIdDest = _tilemapInput[9][9];

// create node to start & dest
	Node* tempStart = _tilemap[nodeIdStart];
	Node* tempDest = _tilemap[nodeIdDest];
// move first node from listVisited
	Node* temp = _tilemap[nodeIdStart];
	listVisited.push(temp);
	temp->SetVisited(true);
// ensure that there will be a path
	if (!listVisited.front())
		return tempVec;
// BFS
	while (!listVisited.empty())
	{
	// pop first node in listVisited
		temp = listVisited.front();
		listVisited.pop();
	// insert neighbours neighbours of temp
		// if (Up exisits && Up !visited && Up !solid)
		if (temp->GetUp() && !temp->GetUp()->GetVisited() && !temp->GetUp()->GetSolid())
		{
			temp->GetUp()->SetPrev(temp);
			if (temp->GetUp() == tempDest)
				break;
			listVisited.push(temp->GetUp());
			temp->GetUp()->SetVisited(true);
		}
		if (temp->GetDown() && !temp->GetDown()->GetVisited() && !temp->GetDown()->GetSolid())
		{
			temp->GetDown()->SetPrev(temp);
			if (temp->GetDown() == tempDest)
				break;
			listVisited.push(temp->GetDown());
			temp->GetDown()->SetVisited(true);
		}
		if (temp->GetLeft() && !temp->GetLeft()->GetVisited() && !temp->GetLeft()->GetSolid())
		{
			temp->GetLeft()->SetPrev(temp);
			if (temp->GetLeft() == tempDest)
				break;
			listVisited.push(temp->GetLeft());
			temp->GetLeft()->SetVisited(true);
		}
		if (temp->GetRight() && !temp->GetRight()->GetVisited() && !temp->GetRight()->GetSolid())
		{
			temp->GetRight()->SetPrev(temp);
			if (temp->GetRight() == tempDest)
				break;
			listVisited.push(temp->GetRight());
			temp->GetRight()->SetVisited(true);
		}
	}
	// after BFS done, reset _tileMap Node.visited to false
	std::unordered_map < size_t, Node* >::iterator itrMap = _tilemap.begin();
	while (itrMap != _tilemap.end())
	{
		itrMap->second->SetVisited(false);
		itrMap->second->SetVisited(false);
		++itrMap;
	}
	// get reversed path (from end node to start node)
	while (temp != tempStart)
	{
		tempVec.push_back(temp);
		temp = temp->GetPrev();
	}
	// reverse tempVec and push to finalVec
	std::vector<Node*>::reverse_iterator itrVec = tempVec.rbegin();
	while (itrVec != tempVec.rend())
	{
		finalVec.push_back(*itrVec++);
	}
	return finalVec;


	// run pathfinding algorithm based on '_curr' toward '_dest'
		// A* (std use) or BFS(more expensive but easier)	
	// TODO: BFS Implementation
}

// AISystem stuff
/////////////////////////
