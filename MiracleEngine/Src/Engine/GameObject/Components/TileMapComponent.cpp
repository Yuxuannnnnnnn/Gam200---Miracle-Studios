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

// NODE stuff
/////////////////////////

/////////////////////////
// AISystem stuff

void TileMapComponent::CalcTileSize()
{
	if (_mapWidth < 0 || _mapHeight < 0)
	{
		std::cout << "WARNING: Map Width||Height < 0\n";
		return;
	}

	Vector3 scale = ((TransformComponent*)GetParentPtr()->GetComponent(ComponentId::CT_Transform))->GetScaleA();
	_tilesize.SetX(scale._x / _mapWidth);
	_tilesize.SetY(scale._y / _mapHeight);
}

void TileMapComponent::CalcOffset()
{
	_mapCenterOffset = Vector3(
		static_cast<float>(((_tilesize._x * _mapWidth) / 2)),
		static_cast<float>(((_tilesize._y * _mapHeight) / 2)),
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
	// create blank _tilemapInput
	int currNode = 0, currId = 0;
	Node* up = nullptr, * down = nullptr, * left = nullptr, * right = nullptr;
	for (unsigned y = 0; y < _mapHeight; ++y)
	{
		for (unsigned x = 0; x < _mapWidth; ++x)
		{
			bool solid = _tilemapInput[y][x] == 1 ? true : false;
			// pos + mapOffset + tile scaling
			_tileNodeMap[currId] = new Node(solid, currId, Vector3(
				x * _tilesize._x + _mapCenterOffset._x + _tilesize._x * x,
				y * _tilesize._y + _mapCenterOffset._y + _tilesize._y * y,
				1)); // set Node pos;
			_tilemapInput[y][x] = currId++; // overwrite the info
		}
	}
	currId = 0;
	// set UpDownLeftRight for new _tileNodeMap;
	for (int y = 0; y < (int)_mapHeight; ++y)
		for (int x = 0; x < (int)_mapWidth; ++x)
		{
			currNode = _tilemapInput[y][x];
			// Left
			if (x > 0)
			{
				currId = _tilemapInput[y][x - 1]; // add left ptr
				left = _tileNodeMap[currId];
				if (DEBUGOUTPUT) std::cout << "L " << currId << " ";
			}
			else
				left = nullptr; // put nullptr
		// Right
			if (x < (int)_mapWidth - 1)
			{
				currId = _tilemapInput[y][x + 1];
				right = _tileNodeMap[currId];
				if (DEBUGOUTPUT) std::cout << "R " << currId << " ";
			}
			else
				right = nullptr;
			// Up
			if (y > 0)
			{
				currId = _tilemapInput[y - 1][x];
				up = _tileNodeMap[currId];
				if (DEBUGOUTPUT) std::cout << "U " << currId << " ";
			}
			else
				up = nullptr;
			// Down
			if (y < (int)_mapHeight - 1)
			{
				currId = _tilemapInput[y + 1][x];
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

void TileMapComponent::DeserialNodeMap()
{
	int currNodeId = 0;
	Node* currNodePtr = nullptr;
	// run through _tileNodeMap and overwrite _tilemapInput[][]
	for (int y = 0; y < (int)_mapHeight; ++y)
		for (int x = 0; x < (int)_mapWidth; ++x)
		{
			currNodePtr = _tileNodeMap[currNodeId++];
			_tilemapInput[y][x] = currNodePtr->GetSolid();
		}
	DeleteNodeMap();
}
void TileMapComponent::DeleteNodeMap()
{
	// free existing _tileNodeMap, _tilemapInput
	for (auto map : _tileNodeMap)
		delete map.second;
	_tileNodeMap.clear();

	for (unsigned i = 0; i < _mapWidth; ++i)
		delete _tilemapInput[i];
	delete _tilemapInput;

	// set map related values to 0
	_mapHeight = _mapWidth = 0;
	_tilesize = Vector3(0, 0, 0);
}

void TileMapComponent::ResizeNodeMap(Vector3 newScale)
{
	// run through all nodes in _tileNodeMap and shift by the x,y offset
	Node* nodePtr = nullptr;
	unsigned currId = 0;
	for (int y = 0; y < (int)_mapHeight; ++y)
		for (int x = 0; x < (int)_mapWidth; ++x)
		{
			nodePtr = _tileNodeMap[currId++];
			nodePtr->SetPosition(
				Vector3(
					nodePtr->GetPosition().GetX() + _mapCenterOffset._x + newScale._x * x,
					nodePtr->GetPosition().GetY() + _mapCenterOffset._y + newScale._y * y,
					1));
		}
}

void TileMapComponent::EditNodeMap(int newHeight, int newWidth)
{
	if (newHeight < 0 || newWidth < 0)
	{
		std::cout << "WARNING: New map Width||Height < 0.\n";
		return;
	}
	// if got change in number of nodes, remake the map
	if ((newHeight != _mapHeight) || (newWidth != _mapWidth))
	{
		// free existing _tileNodeMap, _tilemapInput
		for (auto map : _tileNodeMap)
			delete map.second;
		_tileNodeMap.clear();

		for (unsigned i = 0; i < _mapWidth; ++i)
			delete _tilemapInput[i];
		delete _tilemapInput;

		_mapHeight = newHeight;
		_mapWidth = newWidth;
		CalcTileSize();
		CalcOffset();
		// create blank _tilemapInput
		int currNode = 0, currId = 0;
		Node* up = nullptr, * down = nullptr, * left = nullptr, * right = nullptr;
		_tilemapInput = new int* [_mapHeight]; //mem alloc height
		for (unsigned y = 0; y < _mapHeight; ++y)
		{
			_tilemapInput[y] = new int[_mapWidth]; //mem alloc width
			for (unsigned x = 0; x < _mapWidth; ++x)
			{
				_tileNodeMap[currId] = new Node(false, currId, Vector3(
					x * _tilesize._x + _mapCenterOffset._x + _tilesize._x * x,
					y * _tilesize._y + _mapCenterOffset._y + _tilesize._y * y,
					1)); // set Node pos;
				currId++;
			}
		}
		currId = 0;
		// set UpDownLeftRight for new _tileNodeMap;
		for (int y = 0; y < (int)_mapHeight; ++y)
			for (int x = 0; x < (int)_mapWidth; ++x)
			{
				currNode = _tilemapInput[y][x];
				// Left
				if (x > 0)
				{
					currId = _tilemapInput[y][x - 1]; // add left ptr
					left = _tileNodeMap[currId];
					if (DEBUGOUTPUT) std::cout << "L " << currId << " ";
				}
				else
					left = nullptr; // put nullptr
				// Right
				if (x < (int)_mapWidth - 1)
				{
					currId = _tilemapInput[y][x + 1];
					right = _tileNodeMap[currId];
					if (DEBUGOUTPUT) std::cout << "R " << currId << " ";
				}
				else
					right = nullptr;
				// Up
				if (y > 0)
				{
					currId = _tilemapInput[y - 1][x];
					up = _tileNodeMap[currId];
					if (DEBUGOUTPUT) std::cout << "U " << currId << " ";
				}
				else
					up = nullptr;
				// Down
				if (y < (int)_mapHeight - 1)
				{
					currId = _tilemapInput[y + 1][x];
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

void TileMapComponent::ToggleNodeSolidity(float x, float y)
{
	Node* nodePtr = nullptr;
	// based on x,y get the right node
		//ImGuizmoManager::Update()
			//if (Collision::CollisionCheck(pickingBox, pos))
	nodePtr = nullptr;
	// toggle node _solid
	nodePtr->SetSolid(!nodePtr->GetSolid());
}

// AISystem stuff
/////////////////////////

void TileMapComponent::SerialiseComponent(Serialiser& document)
{
	if (document.HasMember("Width") && document["Width"].IsInt())
		_mapWidth = document["Width"].GetInt();

	if (document.HasMember("Height") && document["Width"].IsInt())
		_mapHeight = document["Height"].GetInt();

	//if (document.HasMember("Palette"))
	//{
	//	for (unsigned i = 0; i < document["Palette"].Size(); i++)
	//	{
	//		palette[document["Palette"][i][0].GetInt()] = document["Palette"][i][1].GetString();
	//	}
	//}

	//if (document.HasMember("Palette"))
	//{
	//	_tilemap = new PaletteType * [_height];

	//	for (int height = 0; height < _height; height++)
	//	{
	//		_tilemap[height] = new PaletteType[_width];

	//		for (int width = 0; width < _width; width++)
	//		{
	//			_tilemap[height][width] = palette[document["TileMap"][height * width + width].GetInt()];
	//		}
	//	}
	//}

}
