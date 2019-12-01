#include "PrecompiledHeaders.h"
#include "AiSystem.h"
#include "Engine/EngineSystems.h"

/////////////////////////
// NODE stuff

Node::Node(bool solid, size_t id, Vector3 pos) :
	_solid{ solid },
	_visited{ false },
	_closed{ false },
	_nodeId{ id },
	_position{ pos },
	_PtrNodeUp{ nullptr },
	_PtrNodeDown{ nullptr },
	_PtrNodeLeft{ nullptr },
	_PtrNodeRight{ nullptr },
	_PtrNodePrev{ nullptr },
	_f{ 0 },
	_g{ 0 },
	_h{ 0 }
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
bool Node::GetClosed()
{
	return _closed;
}
void Node::SetClosed(bool in)
{
	_closed = in;
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

}

// GetSet

std::unordered_map < size_t, Node* > AISystem::GetTileMap()
{
	return _tilemap;
}
void AISystem::SetTileMap(std::unordered_map < size_t, Node* > map)
{
	_tilemap = map;
}
size_t AISystem::GetMapTileSize()
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
	//CreateNodeMap();
	//PathFinding(Vector3(0,0,0), Vector3(0,0,0));
}
void AISystem::Update(double dt)
{
	if (!init)
	{
		Init();
		SetInit();
	}
	
	if (_timer > 0)
	{
		_timer -= dt;
		return;
	}
	else // run AI
		_timer = _timeCooldown;


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
	// offset the map's origin	// pos.x = ( totalMap.x/2 + offset for tile's node ) // _tileMapInput[y][x]
	int originX = -(int)((_mapTileSize * _mapWidth) / 2);
	int originY = -(int)((_mapTileSize * _mapHeight) / 2);
	tempVecOrigin = Vector3((float)originX, (float)originY, 0);
	
	EngineSystems::GetInstance()._physicsSystem->_collisionMap.AddNewMap(
		MAP_HEIGHT, MAP_WIDTH, Vec2{ MAP_SIZE, MAP_SIZE }, tempVecOrigin);

	for (int y = 0; y < (int)_mapHeight; ++y)
	{
		for (int x = 0; x < _mapWidth; ++x)
		{
			// Update tempVec
			tempVec = Vector3(
				tempVecOrigin._x + (x * _mapTileSize), // map grows rightwards
				tempVecOrigin._y + (y * _mapTileSize), // map grows upwards
				0);
			// Create node
			solid = _tilemapInput[y][x] == 1 ? true : false;
			bool spawner = _tilemapInput[y][x] == 2 ? true : false;
			bool spawner2 = _tilemapInput[y][x] == 3 ? true : false;
			bool spawner3 = _tilemapInput[y][x] == 4 ? true : false;
			tempNode = new Node(solid, id, tempVec);
			//_tilemap[id] = tempNode;
			_tilemap.insert(std::pair<size_t, Node*>(id, tempNode));
			// Assign id to the current _tilemap[][]
			_tilemapInput[y][x] = id++; //increment the id
			// create WALL object from factory
			if (solid) 
			{	// create wall only if solid
				tempGo = EngineSystems::GetInstance()._gameObjectFactory->CloneGameObject(EngineSystems::GetInstance()._prefabFactory->GetPrototypeList()[TypeIdGO::WALL]);
				tempGo->Set_typeId(TypeIdGO::WALL);
				((TransformComponent*)tempGo->GetComponent(ComponentId::TRANSFORM_COMPONENT))->SetPos(tempVec);
				
				EngineSystems::GetInstance()._physicsSystem->_collisionMap.AddNewTile(y, x, MapTile{ TileType::HARD_WALL, tempGo->Get_uID() });
				//std::cout << id;
			}
			else if (spawner)
			{	// create spawner if tileMapInput[][] == 2
				GameObject* spawner = nullptr;
				spawner = EngineSystems::GetInstance()._gameObjectFactory->CloneGameObject(EngineSystems::GetInstance()._prefabFactory->GetPrototypeList()[TypeIdGO::SPAWNER]);
				((TransformComponent*)spawner->GetComponent(ComponentId::TRANSFORM_COMPONENT))->SetPos(tempVec);
				
				//std::cout << "*";
			}
			else if (spawner2)
			{	// create spawner if tileMapInput[][] == 3
				GameObject* spawner = nullptr;
				spawner = EngineSystems::GetInstance()._gameObjectFactory->CloneGameObject(EngineSystems::GetInstance()._prefabFactory->GetPrototypeList()[TypeIdGO::SPAWNERTWO]);
				((TransformComponent*)spawner->GetComponent(ComponentId::TRANSFORM_COMPONENT))->SetPos(tempVec);
				
				//std::cout << "*";
			}
			else if (spawner3)
			{	// create spawner if tileMapInput[][] == 4
				GameObject* spawner = nullptr;
				spawner = EngineSystems::GetInstance()._gameObjectFactory->CloneGameObject(EngineSystems::GetInstance()._prefabFactory->GetPrototypeList()[TypeIdGO::SPAWNERTHREE]);
				((TransformComponent*)spawner->GetComponent(ComponentId::TRANSFORM_COMPONENT))->SetPos(tempVec);

				//std::cout << "*";
			}
			else
			{	// create wall only if solid
				tempGo = EngineSystems::GetInstance()._gameObjectFactory->CloneGameObject(EngineSystems::GetInstance()._prefabFactory->GetPrototypeList()[TypeIdGO::FLOOR]);
				tempGo->Set_typeId(TypeIdGO::FLOOR);
				((TransformComponent*)tempGo->GetComponent(ComponentId::TRANSFORM_COMPONENT))->SetPos(tempVec);
				
				//std::cout << "*";
			}
			//std::cout << " ";
		}
		//std::cout << std::endl;
	}

	size_t currNode = 0;
	Node* up, * down, * left, * right;
	// link the Node's updownleftfight
	for (int y = 0; y < (int)_mapHeight; ++y)
		for (int x = 0; x < (int)_mapWidth; ++x)
		{
			currNode = _tilemapInput[y][x];
			// Left
			if (x > 0)
			{
				id = _tilemapInput[y][x - 1]; // add left ptr
				left = _tilemap[id];
				//std::cout << "L " << id << " ";
			}
			else
				left = nullptr; // put nullptr
		// Right
			if (x < (int)_mapWidth - 1)
			{
				id = _tilemapInput[y][x + 1];
				right = _tilemap[id];
				//std::cout << "R " << id << " ";
			}
			else
				right = nullptr;
			// Up
			if (y > 0)
			{
				id = _tilemapInput[y - 1][x];
				up = _tilemap[id];
				//std::cout << "U " << id << " ";
			}
			else
				up = nullptr;
			// Down
			if (y < (int)_mapHeight - 1)
			{
				id = _tilemapInput[y + 1][x];
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
	//for (int y = 0; y < (int)_mapHeight; ++y)
	//{
	//	for (int x = 0; x < (int)_mapWidth; ++x)
	//	{
	//		std::cout << _tilemapInput[y][x] << "\t";
	//	}
	//	std::cout << std::endl;
	//}

	size_t tilesize = (float)EngineSystems::GetInstance()._aiSystem->GetMapTileSize();
	EngineSystems::GetInstance()._graphicsSystem->DrawRockyTile({ 0.0f * tilesize, 0.0f * tilesize,1 }, { 900,900,1 }, 4.0f);
	EngineSystems::GetInstance()._graphicsSystem->DrawRockyTile({ -7.0f * tilesize, 5.0f * tilesize,1 }, { 500,500,1 }, 2.0f);
	EngineSystems::GetInstance()._graphicsSystem->DrawRockyTile({ -10.0f * tilesize, -8.0f * tilesize,1 }, { 1200,900,1 }, 3.0f);
	EngineSystems::GetInstance()._graphicsSystem->DrawRockyTile({ 10.0f * tilesize, 7.0f * tilesize,1 }, { 1200,900,1 }, 1.0f);
	EngineSystems::GetInstance()._graphicsSystem->DrawRockyTile({ 12.0 * tilesize, -7.0f * tilesize,1 }, { 500,600,1 }, 5.0f);

	EngineSystems::GetInstance()._graphicsSystem->DrawCircularBatteryPlatform({ -5.5f * tilesize,-3.5f * tilesize,1 }, { 900,900,1 },4.0f);
	EngineSystems::GetInstance()._graphicsSystem->DrawBuilding2({ 0.0f * tilesize, 3.0f * tilesize,1 }, { 550, 950,1 });
	EngineSystems::GetInstance()._graphicsSystem->DrawBuilding4({ 4.0f * tilesize, 8.5f * tilesize,1 }, { 425, 330,1 }, PI/2);
	EngineSystems::GetInstance()._graphicsSystem->DrawCircularBatteryPlatform({ 5.5f * tilesize, 11.5f * tilesize,1 }, { 400, 400,1 },1.0f);
	EngineSystems::GetInstance()._graphicsSystem->DrawBuilding2({ 10.0f * tilesize, 9.9f * tilesize,1 }, { -450, -580,1 });
	EngineSystems::GetInstance()._graphicsSystem->DrawCircularBatteryPlatform({ 12.0f * tilesize, 1.0f * tilesize,1 }, { 1080, 1080,1 },3.0f);
	EngineSystems::GetInstance()._graphicsSystem->DrawBuilding1({ -6.0f * tilesize, 9.8f * tilesize,1 }, { 1150, 900,1 });
	EngineSystems::GetInstance()._graphicsSystem->DrawBuilding2({ -15.5f * tilesize, 10.9f * tilesize,1 }, { -650, -580,1 });
	EngineSystems::GetInstance()._graphicsSystem->DrawBuilding2({ -15.5f * tilesize, 5.1f * tilesize,1 }, { 650, 580,1 });
	EngineSystems::GetInstance()._graphicsSystem->DrawBuilding4({ -13.0f * tilesize, -11.0f * tilesize,1 }, { 680,780,1 }, PI/2);
	EngineSystems::GetInstance()._graphicsSystem->DrawBuilding3({ 11.5f * tilesize, -9.5f * tilesize,1 }, { 1000, 1000,1 });
	EngineSystems::GetInstance()._graphicsSystem->DrawBuilding4({ 7.5f * tilesize, -9.5f * tilesize,1 }, { 500, 680,1 });
	EngineSystems::GetInstance()._graphicsSystem->DrawBuilding4({ 15.5f * tilesize, -9.5f * tilesize,1 }, { 500, 680,1 });
	//tempGO = EngineSystems::GetInstance()._gameObjectFactory->CreateNewGameObject();
	//tempGO->AddComponent(ComponentId::TRANSFORM_COMPONENT);
	//((TransformComponent*)(tempGO->GetComponent(ComponentId::TRANSFORM_COMPONENT)))->SetPos(Vector3());
	//((TransformComponent*)(tempGO->GetComponent(ComponentId::TRANSFORM_COMPONENT)))->SetScale(Vector3());
	//tempGO->AddComponent(ComponentId::GRAPHICS_COMPONENT);
	//((GraphicComponent*)(tempGO->GetComponent(ComponentId::GRAPHICS_COMPONENT)))->SetFileName("");

	//// top
	//GameObject * obj = EngineSystems::GetInstance()._gameObjectFactory->
	//	CloneGameObject(EngineSystems::GetInstance()._prefabFactory->GetPrototypeList()[TypeIdGO::MAPEDGE]);
	//TransformComponent* com = dynamic_cast<TransformComponent*> (obj->GetComponent(ComponentId::TRANSFORM_COMPONENT));
	//Vector3 position(0, (MAP_HEIGHT - 1)* MAP_SIZE / 2, 1);
	//com->SetPos(position);
	//Vector3 scale(MAP_WIDTH* MAP_SIZE,0,0);
	//com->SetScale(scale);
	//com->SetRotate(((const float)PI));
	// obj = EngineSystems::GetInstance()._gameObjectFactory->
	//	CloneGameObject(EngineSystems::GetInstance()._prefabFactory->GetPrototypeList()[TypeIdGO::MAPEDGE]);
	// com = dynamic_cast<TransformComponent*> (obj->GetComponent(ComponentId::TRANSFORM_COMPONENT));
	//Vector3 position1(0, -((MAP_HEIGHT + 1) * MAP_SIZE/2), 1);
	//com->SetPos(position1);
	//Vector3 scale1(MAP_WIDTH* MAP_SIZE, 0, 0);
	//com->SetScale(scale1);
	//com->SetRotate(0.f);
	// obj = EngineSystems::GetInstance()._gameObjectFactory->
	//	CloneGameObject(EngineSystems::GetInstance()._prefabFactory->GetPrototypeList()[TypeIdGO::MAPEDGE]);
	// com = dynamic_cast<TransformComponent*> (obj->GetComponent(ComponentId::TRANSFORM_COMPONENT));
	//Vector3 position2(-((MAP_WIDTH + 1) * MAP_SIZE/2), 0, 1);
	//com->SetPos(position2);
	//Vector3 scale2(0, MAP_HEIGHT* MAP_SIZE, 0);
	//com->SetScale(scale2);
	//com->SetRotate(-((const float)(PI/2)));
	// obj = EngineSystems::GetInstance()._gameObjectFactory->
	//	CloneGameObject(EngineSystems::GetInstance()._prefabFactory->GetPrototypeList()[TypeIdGO::MAPEDGE]);
	// com = dynamic_cast<TransformComponent*> (obj->GetComponent(ComponentId::TRANSFORM_COMPONENT));
	//Vector3 position3((MAP_WIDTH - 1)* MAP_SIZE / 2, 0, 1);
	//com->SetPos(position3);
	//Vector3 scale3(0, MAP_HEIGHT* MAP_SIZE, 0);
	//com->SetScale(scale3);
	//com->SetRotate(((const float)PI/2));
}

//std::vector<Node*> AISystem::PathFinding(Vector3& _curr, Vector3& _dest)
std::vector<Node*> AISystem::PathFindingOld(Vector3 curr, Vector3 dest)
{
	std::queue<Node*> listVisited;
	float x, y;
	size_t nodeIdStart, nodeIdDest;
	std::vector<Node*> tempVec, finalVec;
	// start node, end node // based on closest postiion, set the start(obj.pos()) and end (target.pos())
				//formula ( (x % _mapTileSize) + _mapTileSize/2 )
		// offset the map's origin	// pos.x = ( totalMap.x/2 + offset for tile's node ) // _tileMapInput[y][x]
		//int originX = -(_mapTileSize * _mapWidth) / 2;
		//int originY = -(_mapTileSize * _mapHeight) / 2;
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
	if (tempStart->GetPosition() == tempDest->GetPosition())
		return std::vector<Node*>();
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

void Node::CalcFGH(Vector3 _start, Vector3 _dest)
{
	Vector3 temp;
	// dist from _curr to _start
	temp = _start - _position;
	_g = (size_t)temp.SquaredLength();
	// dist from _curr to _start
	temp = _dest - _position;
	_h = (size_t)temp.SquaredLength();
	// F
	_f = _g + _h;
}
//std::vector<Node*> AISystem::PathFinding(Vector3& _curr, Vector3& _dest)
std::vector<Node*> AISystem::PathFinding(Vector3 curr, Vector3 dest)
{
	bool testSkip = false; // seems to fix the random crashing

	float x, y;
	size_t nodeIdStart, nodeIdDest;
	std::vector<Node*> tempVec, finalVec;
	std::list<Node*> queOpen;

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

// create node to start & dest
	Node* tempStart = _tilemap[nodeIdStart];
	Node* tempDest = _tilemap[nodeIdDest];
	if (displayDebug)
		std::cout
			<< "tempDest  : " << tempDest->GetNodeId() << " :: "
			<< tempDest->GetPosition()._x << ", " << tempDest->GetPosition()._y
			<< std::endl;
	if (displayDebug)
		std::cout
			<< "tempStart : " << tempStart->GetNodeId() << " :: "
			<< tempStart->GetPosition()._x << ", " << tempStart->GetPosition()._y
			<< std::endl;
	if (nodeIdStart == nodeIdDest)
	{
		if(displayDebug)
			std::cout << "\t Start&End same!" << std::endl;
		finalVec.push_back(tempDest);
		return finalVec;
	}
// A*
	Node* temp = tempStart;
	queOpen.push_back(temp);
	while (temp != tempDest)
	{
	// pop first node in queOpen
		temp = queOpen.front();
		temp->SetClosed(true);
		queOpen.pop_front();
	// insert neighbours neighbours of temp
		// if (Up exisits && Up !closed && Up !solid)
		if (temp->GetUp() && !temp->GetUp()->GetClosed() && !temp->GetUp()->GetSolid())
		{	// UP
			temp->GetUp()->CalcFGH(tempStart->GetPosition(), tempDest->GetPosition());
			temp->GetUp()->SetPrev(temp);
			queOpen.push_back(temp->GetUp());
			//temp->GetUp()->SetClosed(true);
		}
		if (temp->GetDown() && !temp->GetDown()->GetClosed() && !temp->GetDown()->GetSolid())
		{	// DOWN
			temp->GetDown()->CalcFGH(tempStart->GetPosition(), tempDest->GetPosition());
			temp->GetDown()->SetPrev(temp);
			queOpen.push_back(temp->GetDown());
			//temp->GetDown()->SetClosed(true);
		}
		if (temp->GetLeft() && !temp->GetLeft()->GetClosed() && !temp->GetLeft()->GetSolid())
		{	// LEFT
			temp->GetLeft()->CalcFGH(tempStart->GetPosition(), tempDest->GetPosition());
			temp->GetLeft()->SetPrev(temp);
			queOpen.push_back(temp->GetLeft());
			//temp->GetLeft()->SetClosed(true);
		}
		if (temp->GetRight() && !temp->GetRight()->GetClosed() && !temp->GetRight()->GetSolid())
		{	// RIGHT
			temp->GetRight()->CalcFGH(tempStart->GetPosition(), tempDest->GetPosition());
			temp->GetRight()->SetPrev(temp);
			queOpen.push_back(temp->GetRight());
			//temp->GetRight()->SetClosed(true);
		}
		if (queOpen.empty())
		{
			if (displayDebug)
				std::cout << "queOpen.empty()" << std::endl;
			finalVec.push_back(tempDest);
			testSkip = true;
			break;
		}
			
	// take lowest node in queOpen()
		std::list<Node*>::iterator itrQue = queOpen.begin();
		// first loop to find lowest F
		(*itrQue)->_f;
		size_t lowestF = (*itrQue)->_f;
		while (itrQue != queOpen.end())
		{
			if (lowestF > (*itrQue)->_f)
				lowestF = (*itrQue)->_f;
			++itrQue;
		}
		// second loop to get lowest(s)
		std::vector<Node*> occurenceListF;
		itrQue = queOpen.begin();
		while (itrQue != queOpen.end())
		{
			if ((*itrQue)->_f == lowestF)
				occurenceListF.push_back(*itrQue);
			++itrQue;
		}
		if (occurenceListF.size() == 0) // if for some reason got n
		{
			finalVec.push_back(tempStart);
			return finalVec;
		}
		else if (occurenceListF.size() == 1) // single F
		{
			temp = occurenceListF.front();
			// remove and push to front of list
			queOpen.remove(temp);
			queOpen.push_front(temp);
		}
		else // (occurenceList.size() > 1), multiple Fs
		{
			// since got multiple lowest Fs, find lowest H
			std::vector<Node*>::iterator itrVec = occurenceListF.begin();
			size_t lowestH = (*itrVec)->_h;
			while (itrVec != occurenceListF.end())
			{
				if (lowestH < (*itrVec)->_h)
					lowestH = (*itrVec)->_h;
				++itrVec;
			}
			// second loop to get lowest(s)
			std::vector<Node*> occurenceListH;
			itrVec = occurenceListF.begin();
			while (itrVec != occurenceListF.end())
			{
				if (lowestH == (*itrVec)->_h)
					occurenceListH.push_back(*itrVec);
				++itrVec;
			}
			// if no lowest H, just take any
			temp = occurenceListH.front();
			queOpen.remove(temp);
			queOpen.push_front(temp);
		}
	}

	if (!testSkip)
	{
		// get reversed path (from end node to start node)
		temp = tempDest;
		while (temp != tempStart)
		{
			tempVec.push_back(temp);
			temp = temp->GetPrev();
		}
		// reverse tempVec and push to finalVec
		std::vector<Node*>::reverse_iterator itrVecReverse;
		itrVecReverse = tempVec.rbegin();
		while (itrVecReverse != tempVec.rend())
		{
			if (displayDebug)
				std::cout << ((Node*)* itrVecReverse)->GetNodeId() << ", ";
			finalVec.push_back(*itrVecReverse++);
		}
		if (displayDebug)
			std::cout << std::endl;
	}
// after A* done, reset _tileMap Node.Closed to false
	std::unordered_map < size_t, Node* >::iterator itrMap = _tilemap.begin();
	while (itrMap != _tilemap.end())
	{
		if (itrMap->second)
		{
			itrMap->second->SetClosed(false);
			itrMap->second->SetPrev(nullptr);
		}
		++itrMap;
	}
	return finalVec;
}

// AISystem stuff
/////////////////////////
