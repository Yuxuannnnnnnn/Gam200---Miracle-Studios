#include "PrecompiledHeaders.h"
#include "AiSystem.h"

/////////////////////////
// NODE stuff

Node::Node(bool solid, size_t id, Vector3 pos) :
	_solid{ solid },
	_visited{ false },
	_nodeId{ id },
	_position{ pos },
	_PtrNodeUp{ nullptr },
	_PtrNodeDown{ nullptr },
	_PtrNodeLeft{ nullptr },
	_PtrNodeRight{ nullptr },
	_PtrNodePrev{ nullptr }
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

AISystem::AISystem()
{
	init = false;
	_timeUpdateRate = 0;
	_timeUpdatePrev = 0;
	_timeUpdateElapsed = 0;
}

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
unsigned AISystem::GetMapTileSize()
{
	return _mapTileSize;
}
void AISystem::SetInit()
{
	init = true;
}


// InUpEx
void AISystem::Init()
{
	CreateNodeMap();
	//PathFinding();
}
void AISystem::Update(double currTime)
{
	if (!init)
	{
		Init();
		SetInit();
	}

	// update will occur only every ~0.5 seconds
		//_timeUpdateElapsed = (currTime - _timeUpdatePrev);
		//if (_timeUpdateElapsed < _timeUpdateRate)
		//	return;
		//else // run AI
		//	_timeUpdatePrev = currTime;

}
void AISystem::Exit()
{
}

void AISystem::CreateNodeMap()
{
	size_t id = 0; // id for Node's id
	Node* tempNode = nullptr;
	bool solid = false;
	GameObject* tempGo;
	Vector3 tempVec;
	Vector3 tempVecOrigin;
	// offset the map's origin	// pos.x = ( totalMap.x/2 + offset for tile's node )
	int originY = (int)( ((_mapTileSize * _mapHeight) / 2) + _mapHeight / 2);
	int originX = -(int)( ((_mapTileSize * _mapWidth) / 2) + _mapWidth / 2);
	tempVecOrigin = Vector3((float)originX, (float)originY, 0);
	
	for (int i = 0; i < (int)_mapHeight; ++i)
	{
		for (int j = 0; j < (int)_mapWidth; ++j)
		{
			// Update tempVec
			tempVec = Vector3(
				tempVecOrigin._x + (j * _mapTileSize), // map grows rightwards
				tempVecOrigin._y - (i * _mapTileSize), // map grows downwards
				0);
			// Create node
			solid = _tilemapInput[i][j] == 1 ? true : false;
			tempNode = new Node(solid, id, tempVec);
			//_tilemap[id] = tempNode;
			_tilemap.insert(std::pair<size_t, Node*>(id, tempNode));
			// Assign id to the current _tilemap[][]
			_tilemapInput[i][j] = id++; //increment the id
			// create WALL object from factory
			if (solid) // create wall only if solid
			{
				tempGo = EngineSystems::GetInstance()._gameObjectFactory->CloneGameObject(EngineSystems::GetInstance()._prefabFactory->GetPrototypeList()[TypeIdGO::WALL]);
				tempGo->Set_typeId(TypeIdGO::WALL);
				((TransformComponent*)tempGo->GetComponent(ComponentId::TRANSFORM_COMPONENT))->SetPos(tempVec);
			}
			else // create wall only if solid
			{
				tempGo = EngineSystems::GetInstance()._gameObjectFactory->CloneGameObject(EngineSystems::GetInstance()._prefabFactory->GetPrototypeList()[TypeIdGO::FLOOR]);
				tempGo->Set_typeId(TypeIdGO::FLOOR);
				((TransformComponent*)tempGo->GetComponent(ComponentId::TRANSFORM_COMPONENT))->SetPos(tempVec);
			}
		}
	}

	size_t currNode = 0;
	Node* up, * down, * left, * right;
	// link the Node's updownleftfight
	for (int i = 0; i < (int)_mapHeight; ++i)
		for (int j = 0; j < (int)_mapWidth; ++j)
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
			if (j < (int)_mapWidth - 1)
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
			if (i < (int)_mapHeight - 1)
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
	for (int i = 0; i < (int)_mapHeight; ++i)
	{
		for (int j = 0; j < (int)_mapWidth; ++j)
		{
			std::cout << _tilemapInput[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

//std::vector<Node*> AISystem::PathFinding(Vector3& _curr, Vector3& _dest)
std::vector<Node*> AISystem::PathFinding(Vector3 curr, Vector3 dest)
{
	std::queue<Node*> listVisited;
	float x, y;
	size_t nodeIdStart, nodeIdDest;
	std::vector<Node*> tempVec, finalVec;
	// start node, end node // based on closest postiion, set the start(obj.pos()) and end (target.pos())
				//formula ( (x % _mapTileSize) + _mapTileSize/2 )
	x = (curr._x / _mapTileSize);
	y = (curr._y / _mapTileSize);
	x += (_mapWidth / 2); // compensate for the map origin shift
	(x <= 0.f) ? x = 0.f : x;
	(x >= _mapWidth) ? x = (float)_mapWidth : x;
	y += (_mapHeight / 2); // compensate for the map origin shift
	(y <= 0.f) ? y = 0.f : y;
	(y >= _mapHeight) ? y = (float)_mapHeight : y;
	nodeIdStart = _tilemapInput[(int)y][(int)x];
						//std::cout << "curr " << nodeIdStart << std::endl;
	x = (dest._x / _mapTileSize);
	y = (dest._y / _mapTileSize);
	x += (_mapWidth / 2); // compensate for the map origin shift
	(x <= 0.f) ? x = 0.f : x;
	(x >= _mapWidth) ? x = (float)_mapWidth : x;
	y += (_mapHeight / 2); // compensate for the map origin shift
	(y <= 0.f) ? y = 0.f : y;
	(y >= _mapHeight) ? y = (float)_mapHeight : y;
	nodeIdDest = _tilemapInput[(int)y][(int)x];
						//std::cout << "dest " << nodeIdDest << std::endl;

			// fake start end nodes
	//nodeIdStart = _tilemapInput[0][0];
	//nodeIdDest = _tilemapInput[9][9];

	// create node to start & dest
	Node* tempStart = _tilemap[nodeIdStart];
	Node* tempDest = _tilemap[nodeIdDest];
	// move first node from listVisited
	Node* temp = _tilemap[nodeIdStart];
	listVisited.push(temp);
	temp->SetVisited(true);

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
							//std::cout << ((Node*)* itrVec)->GetNodeId() << ", ";
		finalVec.push_back(*itrVec++);
	}
							//std::cout << std::endl;

	// after BFS done, reset _tileMap Node.visited to false
	std::unordered_map < size_t, Node* >::iterator itrMap = _tilemap.begin();
	while (itrMap != _tilemap.end())
	{
		if (itrMap->second)
		{
			itrMap->second->SetVisited(false);
			itrMap->second->SetPrev(nullptr);
		}
		++itrMap;
	}
	return finalVec;


	// run pathfinding algorithm based on '_curr' toward '_dest'
		// A* (std use) or BFS(more expensive but easier)	
	// TODO: BFS Implementation
}

// AISystem stuff
/////////////////////////
