#include "PrecompiledHeaders.h"
#include "TileMapComponent.h"

/////////////////////////
// NODE stuff

Node::Node(bool solid, int id, Vector3 pos) :
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
{
}
Node::~Node()
{
}

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
void Node::SetSolid(bool in)
{
	_solid = in;
}
int Node::GetNodeId()
{
	return _nodeId;
}
Vector3 Node::GetPosition()
{
	return _position;
}
void Node::SetPosition(Vector3 pos)
{
	_position = pos;
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

// NODE stuff
/////////////////////////


//Function to Calculate the TileSize based on the TransformComponent World Scale
void TileMapComponent::CalcTileSize()
{
	if (_mapWidth < 0 || _mapHeight < 0)
	{
		std::cout << "WARNING: Map Width||Height < 0\n";
		return;
	}

	Vector3 scale = ((TransformComponent*)GetParentPtr()->GetComponent(ComponentId::CT_Transform))->GetScaleA();
	_tilesize.SetX(scale._x / (float)(_mapWidth));
	_tilesize.SetY(scale._y / (float)(_mapHeight));
}

//Calculate OffSet of tileMap from the Center of TileMap Object
void TileMapComponent::CalcOffset()
{
	_mapCenterOffset = Vector3(
		static_cast<float>(((_tilesize._x * _mapWidth) / 2.0f)),
		static_cast<float>(((_tilesize._y * _mapHeight) / 2.0f)),
		1);
	//tempVecOrigin = Vector3((float)originX, (float)originY, 0);
	//tempVec = Vector3(
	//	tempVecOrigin._x + (x * _mapTileSize), // map grows rightwards
	//	tempVecOrigin._y + (y * _mapTileSize), // map grows upwards
	//	0);
}

void TileMapComponent::SerialNodeMap()
{
	if (_mapWidth < 0 || _mapHeight < 0)
	{
		std::cout << "WARNING: New map Width||Height||Size < 0\n";
		return;
	}
	CalcTileSize();
	CalcOffset();

	// create blank _tilemapId
	int currNode = 0, currId = 0;
	Node* up = nullptr, * down = nullptr, * left = nullptr, * right = nullptr;

	TransformComponent* transCom = (TransformComponent*)(GetSibilingComponent(ComponentId::CT_Transform));
	Vector3 TileMapCenterPosition = transCom->GetPositionA();

	for (unsigned y = 0; y < _mapHeight; ++y)
	{
		for (unsigned x = 0; x < _mapWidth; ++x)
		{
			bool solid = _tilemapInput[y][x] == 1 ? true : false;

			//center of tileMap - mapcenteroffset + tilesize * y + tilesize/2
			Vector3 position = Vector3(TileMapCenterPosition.GetX() - _mapCenterOffset.GetX() + (_tilesize.GetX() * (float)(x) /*+ (_tilesize.GetX()/2.0f)*/),
				TileMapCenterPosition.GetY() - _mapCenterOffset.GetY() + (_tilesize.GetY() * (float)(y)/*+ (_tilesize.GetY() / 2.0f)*/),
				1);

			_tileNodeMap[currId] = new Node(solid, currId, position); // set Node pos;
			_tilemapId[y][x] = currId++;
		}
	}

	currId = 0;
	// set UpDownLeftRight for new _tileNodeMap;
	for (int y = 0; y < _mapHeight; ++y)
		for (int x = 0; x < _mapWidth; ++x)
		{
			currNode = _tilemapId[y][x];
			// Left
			if (x > 0)
			{
				currId = _tilemapId[y][x - 1]; // add left ptr
				left = _tileNodeMap[currId];
				if (DEBUGOUTPUT) std::cout << "L " << currId << " ";
			}
			else
				left = nullptr; // put nullptr
		// Right
			if (x < (int)(_mapWidth - 1))
			{
				currId = _tilemapId[y][x + 1];
				right = _tileNodeMap[currId];
				if (DEBUGOUTPUT) std::cout << "R " << currId << " ";
			}
			else
				right = nullptr;
			// Down
			if (y > 0) 
			{
				currId = _tilemapId[y - 1][x]; 
				up = _tileNodeMap[currId];
				if (DEBUGOUTPUT) std::cout << "U " << currId << " ";
			}
			else
				up = nullptr;
			// Up
			if (y < (int)_mapHeight - 1) 
			{
				currId = _tilemapId[y + 1][x]; // May Edit to minus
				down = _tileNodeMap[currId];
				if (DEBUGOUTPUT) std::cout << "D " << currId << " ";
			}
			else
				down = nullptr;
			// Set Adjacent Nodes
			if (DEBUGOUTPUT) std::cout << std::endl;
			_tileNodeMap[currNode]->SetNodeAdjacent(up, down, left, right);
		}
	// remove the Input map
	for (unsigned i = 0; i < _mapWidth; ++i)
		delete _tilemapInput[i];
	delete _tilemapInput;
	_tilemapInput = nullptr;
}

//void TileMapComponent::DeserialNodeMap()
//{
//	int currNodeId = 0;
//	Node* currNodePtr = nullptr;
//	// create new 2d array for output
//	_tilemapInput = new int* [_mapHeight]; //mem alloc height
//	for (unsigned y = 0; y < _mapHeight; ++y)
//	{
//		_tilemapInput[y] = new int[_mapWidth]; //mem alloc width
//		for (unsigned x = 0; x < _mapWidth; ++x)
//		{
//			currNodePtr = _tileNodeMap[currNodeId++];
//			_tilemapInput[y][x] = currNodePtr->GetSolid();
//		}
//	}
//}

void TileMapComponent::DeleteNodeMap()
{
	// free existing _tileNodeMap, _tilemapId
	for (auto& map : _tileNodeMap)
		delete map.second;
	_tileNodeMap.clear();

	for (unsigned i = 0; i < _mapHeight; ++i)
	{
		delete _tilemapId[i];
		delete _tilemapInput[i];
	}
	delete _tilemapId;
	delete _tilemapInput;

	// set map related values to 0
	_mapHeight = _mapWidth = 0;
	_tilesize = _mapCenterOffset = Vector3(0, 0, 0);
	_tilemapId = _tilemapInput = nullptr;
}

//If Scale of TileMap is changed or position of TileMap is changed
void TileMapComponent::ResizeNodeMap()
{
	// run through all nodes in _tileNodeMap and shift by the x,y offset
	Node* nodePtr = nullptr;
	// check mapOffset & scale change
	Vector3 prevOffset = _mapCenterOffset; // save previous mapOffset

	CalcTileSize();//Recalculate TileSize before calculat new offset

	CalcOffset();//Recalculate Offset

	//Vector3 offsetChange(
	//	prevOffset._x -_mapCenterOffset._x,
	//	prevOffset._y - _mapCenterOffset._y,
	//	1);
	//
	////Vector3 scaleChange(
	////	newScale._x - _tilesize._x,
	////	newScale._y - _tilesize._y,
	////	1);
	//
	//for (int y = 0; y < _mapHeight; ++y)
	//	for (int x = 0; x < _mapWidth; ++x)
	//	{
	//		nodePtr = _tileNodeMap[currId++];
	//		nodePtr->SetPosition(
	//			Vector3(
	//				nodePtr->GetPosition().GetX() + offsetChange._x + scaleChange._x * x,
	//				nodePtr->GetPosition().GetY() + offsetChange._y + scaleChange._y * y,
	//				1));
	//	}
	unsigned currId = 0;

	TransformComponent* transCom = (TransformComponent*)(GetSibilingComponent(ComponentId::CT_Transform));
	Vector3 TileMapCenterPosition = transCom->GetPositionA();

	for (unsigned y = 0; y < _mapHeight; ++y)
	{
		for (unsigned x = 0; x < _mapWidth; ++x)
		{
			//center of tileMap - mapcenteroffset + tilesize * y + tilesize/2
			_tileNodeMap[currId]->SetPosition(Vector3(TileMapCenterPosition.GetX() - _mapCenterOffset.GetX() + (_tilesize.GetX() * (float)(x) +(_tilesize.GetX() / 2.0f)),
				TileMapCenterPosition.GetY() - _mapCenterOffset.GetY() + (_tilesize.GetY() * (float)(y)+(_tilesize.GetY() / 2.0f)),
				1));
			currId++;
		}
	}
}

//If Height and Width is changed - All Node will return back to nonsolidity
void TileMapComponent::EditNodeMap(int newHeight, int newWidth)
{

	if (newHeight <= 0 || newWidth <= 0)
	{
		std::cout << "WARNING: New map Width||Height <= 0.\n";

		if (_mapHeight != 0 && _mapWidth != 0) //if previous height and width is 0
		{

			// free existing _tileNodeMap, _tilemapId
			for (auto& map : _tileNodeMap)
				delete map.second;
			_tileNodeMap.clear();

			for (unsigned i = 0; i < _mapHeight; ++i)
			{
				delete _tilemapId[i];
				delete _tilemapInput[i];
			}
			delete _tilemapId;
			delete _tilemapInput;

		}

		_mapHeight = newHeight;
		_mapWidth = newWidth;
		return;
	}
	// if got change in number of nodes, remake the map
	if ((newHeight != _mapHeight) || (newWidth != _mapWidth ))
	{

		if (_mapHeight != 0 && _mapWidth != 0) //if previous height and width is 0
		{

			// free existing _tileNodeMap, _tilemapId
			for (auto& map : _tileNodeMap)
				delete map.second;
			_tileNodeMap.clear();

			for (unsigned i = 0; i < _mapHeight; ++i)
			{
				delete _tilemapId[i];
				delete _tilemapInput[i];
			}
			delete _tilemapId;
			delete _tilemapInput;

		}

		_mapHeight = newHeight;
		_mapWidth = newWidth;

		CalcTileSize();
		CalcOffset();

		// create blank _tilemapId
		int currNode = 0, currId = 0;
		Node* up = nullptr, * down = nullptr, * left = nullptr, * right = nullptr;

		TransformComponent* transCom = (TransformComponent*)(GetSibilingComponent(ComponentId::CT_Transform));
		Vector3 TileMapCenterPosition = transCom->GetPositionA();

		_tilemapInput = new int* [_mapHeight];
		_tilemapId = new tileNumber * [_mapHeight];

		for (unsigned y = 0; y < _mapHeight; ++y)
		{
			_tilemapInput[y] = new int[_mapWidth];
			_tilemapId[y] = new tileNumber[_mapWidth];

			for (unsigned x = 0; x < _mapWidth; ++x)
			{
				//center of tileMap - mapcenteroffset + tilesize * y + tilesize/2
				Vector3 position = Vector3(TileMapCenterPosition.GetX() - _mapCenterOffset.GetX() + (_tilesize.GetX() * (float)(x) + (_tilesize.GetX() / 2.0f)),
					TileMapCenterPosition.GetY() - _mapCenterOffset.GetY() + (_tilesize.GetY() * (float)(y)+ (_tilesize.GetY() / 2.0f)),
					1);

				_tileNodeMap[currId] = new Node(false, currId, position); // set Node pos;
				_tilemapId[y][x] = currId;
				_tilemapInput[y][x] = false;
				currId++;
			}
		}

		currId = 0;
		// set UpDownLeftRight for new _tileNodeMap;
		for (int y = 0; y < (int)_mapHeight; ++y)
			for (int x = 0; x < (int)_mapWidth; ++x)
			{
				currNode = _tilemapId[y][x];
				// Left
				if (x > 0)
				{
					currId = _tilemapId[y][x - 1]; // add left ptr
					left = _tileNodeMap[currId];
					if (DEBUGOUTPUT) std::cout << "L " << currId << " ";
				}
				else
					left = nullptr; // put nullptr
				// Right
				if (x < (int)_mapWidth - 1)
				{
					currId = _tilemapId[y][x + 1];
					right = _tileNodeMap[currId];
					if (DEBUGOUTPUT) std::cout << "R " << currId << " ";
				}
				else
					right = nullptr;
				// Down
				if (y > 0)
				{
					currId = _tilemapId[y - 1][x];
					up = _tileNodeMap[currId];
					if (DEBUGOUTPUT) std::cout << "U " << currId << " ";
				}
				else
					up = nullptr;
				// Up
				if (y < (int)_mapHeight - 1)
				{
					currId = _tilemapId[y + 1][x];
					down = _tileNodeMap[currId];
					if (DEBUGOUTPUT) std::cout << "D " << currId << " ";
				}
				else
					down = nullptr;
				// Set Adjacent Nodes
				if (DEBUGOUTPUT) std::cout << std::endl;
				_tileNodeMap[currNode]->SetNodeAdjacent(up, down, left, right);
			}
	}
}

//For Picking on the TileMap Editor
//void TileMapComponent::ToggleNodeSolidity(float x, float y)
//{
//	Node* nodePtr = nullptr;
//	// based on x,y get the right node
//		//ImGuizmoManager::Update()
//			//if (Collision::CollisionCheck(pickingBox, pos))
//	// toggle node _solid
//	nodePtr->SetSolid(!nodePtr->GetSolid());
//
//}


//Function to edit NodeMap when the position in transform position is edited.
void TileMapComponent::Inspect()
{
	if (!turnOnTileMap) //If false
	{
		if (ImGui::Button("Turn ON TileMapEditor "))
		{
			turnOnTileMap = true;
			MyInspectionWindow.SetTileMapEditor(true);
		}
	}
	else if (turnOnTileMap) // if true
	{
		 if (ImGui::Button("Turn OFF TileMapEditor"))
		 {
			 turnOnTileMap = false;
			 MyInspectionWindow.SetTileMapEditor(false);
		 }
	}


	if (turnOnTileMap) //If the TileMapEditor is turn on in the TileMapComponent Editor
	{
		ImGui::Spacing();
		ImGui::Spacing();

		static int height = _mapHeight;
		static int width = _mapWidth;

		if (ImGui::InputInt("Height ", &height))
		{
			EditNodeMap(height, _mapWidth);

		}

		ImGui::Spacing();
		ImGui::Spacing();
		if (ImGui::InputInt("Width ", &width))
		{
			EditNodeMap(_mapHeight, width);
		}

		ImGui::Spacing();
		ImGui::Spacing();

		Vector3  pos = MyInputSystem.GetMouseWorldPos();

		//Check Picking Collision for every single tile
		for (auto& tile : _tileNodeMap)
		{
			//Draw every Tile                                       // x center                     y center
			DebugRenderer::GetInstance().DrawBox(glm::vec3{ tile.second->GetPosition()._x, tile.second->GetPosition()._y, 0 },
				   // x y scale
				glm::vec3{ _tilesize._x, _tilesize._y,0 });

			std::cout << tile.second->GetPosition() << ", " << _tilesize << std::endl;

			TransformComponent * transform = (TransformComponent*)(GetSibilingComponent(ComponentId::CT_Transform));

			//Create a picking Box for each tile, position, tilesize and rotation
			BPolygon pickingBox = BPolygon::CreateBoxPolygon(Vec3{ tile.second->GetPosition()._x,tile.second->GetPosition()._y, 1.0f },
				Vec3{ _tilesize._x, _tilesize._y },
				transform->GetRotate());

			//If there is collision
			if (Collision::CollisionCheck(pickingBox, pos))
			{
				if (MyInputSystem.KeyDown(MOUSE_RBUTTON))	//If the tile is selcted
				{
					tile.second->SetSolid(!tile.second->GetSolid());
				}
				else										// If just Hovering over the box
				{
					DebugRenderer::GetInstance().FillBox(glm::vec3{ tile.second->GetPosition().GetX(),tile.second->GetPosition().GetY(),0 }, glm::vec3{ _tilesize._x, _tilesize._y,0 }, glm::vec4{ 1, 0, 0, 0.3f });
				}
			}

			if (tile.second->GetSolid())
			{
				//DebugRenderer::GetInstance().FillBox(glm::vec3{ tile.second->GetPosition().GetX(),tile.second->GetPosition().GetY(),0 }, glm::vec3{ _tilesize._x, _tilesize._y,0 }, glm::vec4{ 1, 0, 0, 0.7f });
			}

		}
	}


}



void TileMapComponent::SetMapHeight(int in)
{
	_mapHeight = in;
}
int TileMapComponent::GetMapHeight()
{
	return _mapHeight;
}
void TileMapComponent::SetMapWidth(int in)
{
	_mapWidth = in;
}
int TileMapComponent::GetMapWidth()
{
	return _mapWidth;
}
Vector3 TileMapComponent::GetTilesize()
{
	return _tilesize;
}
int** TileMapComponent::GetTilemapId()
{
	return _tilemapId;
}
std::unordered_map < int, Node* > TileMapComponent::GetNodeMap()
{
	return _tileNodeMap;
}