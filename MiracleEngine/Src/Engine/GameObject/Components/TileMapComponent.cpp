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
	_NodeObj{ nullptr },
	_f{ 0 },
	_g{ 0 },
	_h{ 0 }
{
	_NodeObj = MyFactory.CloneGameObject(MyResourceSystem.GetPrototypeMap()["Node"]);
	((TransformComponent*)_NodeObj->GetComponent(ComponentId::CT_Transform))->SetPos(_position);
}
Node::~Node()
{
	_NodeObj->SetDestory();
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
	((TransformComponent*)_NodeObj->GetComponent(ComponentId::CT_Transform))->SetPos(_position);
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

void TileMapComponent::CreateNodeMap(int width, int height)
{
	if (width < 0 || height < 0)
	{
		std::cout << "WARNING: New map Width||Height||Size < 0\n";
		return;
	}

	// free existing _tileNodeMap, _tilemapInput
	for (auto map : _tileNodeMap)
		delete map.second;
	_tileNodeMap.clear();

	for (unsigned i = 0; i < _mapWidth; ++i)
		delete _tilemapInput[i];
	delete _tilemapInput;

	// create blank _tilemapInput
	int currNode = 0, currId = 0;
	Node* up = nullptr, * down = nullptr, * left = nullptr, * right = nullptr;
	_tilemapInput = new int* [height]; //mem alloc height
	for (unsigned y = 0; y < height; ++y)
	{
		_tilemapInput[y] = new int[width]; //mem alloc width
		for (unsigned x = 0; x < width; ++x)
		{
			_tilemapInput[y][x] = currId;
			_tileNodeMap[currId] = new Node(false, currId, Vector3(x * _tilesize._x, y * _tilesize._y, 1)); // set Node pos;
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

void TileMapComponent::CreateNodeMap(int width, int height, Vector3 offset, Vector3 scaleset)
{
	if (width < 0 || height < 0)
	{
		std::cout << "WARNING: New map Width||Height||Size < 0\n";
		return;
	}

	// free existing _tileNodeMap, _tilemapInput
	for (auto map : _tileNodeMap)
		delete map.second;
	_tileNodeMap.clear();

	for (unsigned i = 0; i < _mapWidth; ++i)
		delete _tilemapInput[i];
	delete _tilemapInput;

	// create blank _tilemapInput
	int currNode = 0, currId = 0;
	Node* up = nullptr, * down = nullptr, * left = nullptr, * right = nullptr;
	_tilemapInput = new int* [height]; //mem alloc height
	for (unsigned y = 0; y < height; ++y)
	{
		_tilemapInput[y] = new int[width]; //mem alloc width
		for (unsigned x = 0; x < width; ++x)
		{
			_tilemapInput[y][x] = currId;
			_tileNodeMap[currId] = new Node(false, currId, Vector3(
				x * _tilesize._x + offset._x + scaleset._x * x,
				y * _tilesize._y + offset._y + scaleset._y * y,
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

void TileMapComponent::ResizeNodeMap(Vector3 offset, Vector3 scaleset)
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
					nodePtr->GetPosition().GetX() + offset._x + scaleset._x * x,
					nodePtr->GetPosition().GetY() + offset._y + scaleset._y * y,
					1));
		}
}

void TileMapComponent::EditNodeMap(int newHeight, int newWidth, Vector3 offset, Vector3 scaleset)
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
					x * _tilesize._x + offset._x + scaleset._x * x,
					y * _tilesize._y + offset._y + scaleset._y * y,
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
