#include "PrecompiledHeaders.h"
#include "AiSystem.h"

AISystem::AISystem() :
	_init{ false },
	_timer{ 0 }, _timeCooldown{ 0 }
{
}

// InUpEx
void AISystem::Init()
{
	UpdateNodeMapGO();
	_init = true;
}
void AISystem::Update(double dt)
{
	if (!_init)
		Init();
	if (_timer > 0) // AI updates every _timerCooldown
	{
		_timer -= dt;
		return;
	}
	_timer = _timeCooldown;


}
void AISystem::Exit()
{
}

/*
//For Editor
	bool turnOnTileMap; //Bool to activate drawing in GraphicSystem to draw tiles.
	Vector3 _mapCenterOffset; // the map's local center offset from bottom left, use this when calculating offset
	Vector3 _tilesize; //x, y //tilesize will be calculated from scale in transformComponent.
					//Everytime Scaling changes, tilesize is recalculated.

	int _mapHeight, _mapWidth;

	typedef int tileNumber;
	std::unordered_map < tileNumber, Node* > _tileNodeMap; // <NodeId, NodePtr>

	tileNumber** _tilemapId; // 2dArray of the NodeMap in ID form
	tileNumber** _tilemapInput; // 2dArray of node solidity
	*/
void AISystem::UpdateNodeMapGO()
{
	// get the GO with TileMapComponent
	for (auto idPair : _engineSystems._factory->getObjectlist())
	{
		if (((IdentityComponent*)idPair.second->GetComponent(ComponentId::CT_Identity))->ObjectType().compare("TileMap") == 0 ||
			((IdentityComponent*)idPair.second->GetComponent(ComponentId::CT_Identity))->ObjectType().compare("Tilemap") == 0 ||
			((IdentityComponent*)idPair.second->GetComponent(ComponentId::CT_Identity))->ObjectType().compare("tilemap") == 0 ||
			((IdentityComponent*)idPair.second->GetComponent(ComponentId::CT_Identity))->ObjectType().compare("tileMap") == 0)
		{
			NodeMapGO = idPair.second;
			NodeMapGOId = idPair.second->Get_uID();
			break;
		}  //MyFactory.GetObjectWithId(_targetUid) use this when getting the GO
	}
	if (!NodeMapGO)
	{
		std::cout << "WARNING: NodeMapGO is nullptr.\n";
		NodeMapGOId = 0;
		return;
	}
	TileMapComponent* map = (TileMapComponent*)NodeMapGO;
	// values from NodeMapGO
	_mapTileSize = map->GetTilesize(); // replacing _tilesize
	_mapHeight = map->GetMapHeight();
	_mapWidth = map->GetMapWidth();
	_tilemapId = map->GetTilemapId(); //tileNumber** _tilemapId
	_tileNodeMap = map->GetNodeMap();
}

std::vector<Node*> AISystem::PathFinding(Vector3 curr, Vector3 dest)
{
	bool testSkip = false; // seems to fix the random crashing

	float x, y;
	int nodeIdStart, nodeIdDest;
	std::vector<Node*> tempVec, finalVec;
	std::list<Node*> queOpen;

	x = (curr._x / _mapTileSize._x);
	y = (curr._y / _mapTileSize._y);
	x += (_mapWidth / 2); // compensate for the map origin shift
	(x <= 0.f) ? x = 0.f : x;
	(x >= _mapWidth) ? x = (float)_mapWidth : x;
	y += (_mapHeight / 2); // compensate for the map origin shift
	(y <= 0.f) ? y = 0.f : y;
	(y >= _mapHeight) ? y = (float)_mapHeight : y;
	nodeIdStart = _tilemapId[(int)y][(int)x];
	//std::cout << "curr " << nodeIdStart << std::endl;
	x = (dest._x / _mapTileSize._x);
	y = (dest._y / _mapTileSize._y);
	x += (_mapWidth / 2); // compensate for the map origin shift
	(x <= 0.f) ? x = 0.f : x;
	(x >= _mapWidth) ? x = (float)_mapWidth : x;
	y += (_mapHeight / 2); // compensate for the map origin shift
	(y <= 0.f) ? y = 0.f : y;
	(y >= _mapHeight) ? y = (float)_mapHeight : y;
	nodeIdDest = _tilemapId[(int)y][(int)x];
	//std::cout << "dest " << nodeIdDest << std::endl;

// create node to start & dest
	Node* tempStart = _tileNodeMap[nodeIdStart];
	Node* tempDest = _tileNodeMap[nodeIdDest];
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
		if (displayDebug)
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
				std::cout << ((Node*)*itrVecReverse)->GetNodeId() << ", ";
			finalVec.push_back(*itrVecReverse++);
		}
		if (displayDebug)
			std::cout << std::endl;
	}
	// after A* done, reset _tileMap Node.Closed to false
	auto itrMap = _tileNodeMap.begin();
	while (itrMap != _tileNodeMap.end())
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




/*

//std::vector<Node*> AISystem::PathFinding(Vector3& _curr, Vector3& _dest)
std::vector<Node*> AISystem::PathFindingOld(Vector3 curr, Vector3 dest)
{
	std::queue<Node*> listVisited;
	float x, y;
	int nodeIdStart, nodeIdDest;
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
	Node* tempStart = _tileNodeMap[nodeIdStart];
	Node* tempDest = _tileNodeMap[nodeIdDest];
	if (tempStart->GetPosition() == tempDest->GetPosition())
		return std::vector<Node*>();
	// move first node from listVisited
	Node* temp = _tileNodeMap[nodeIdStart];
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
	auto itrMap = _tileNodeMap.begin();
	while (itrMap != _tileNodeMap.end())
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
*/
