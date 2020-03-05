#pragma once
#include "GameObject/IComponent.h"

class Node {
private:
	bool _solid;	// to prevent usage of node
	bool _visited;	// use for BFS algorithm
	bool _closed; // Astar
	int _nodeId;
	Vector3 _position;	// position of Node in  World
// Node pointers
	Node* _PtrNodeUp;
	Node* _PtrNodeDown;
	Node* _PtrNodeLeft;
	Node* _PtrNodeRight;
	Node* _PtrNodePrev;
public:

	size_t _f, _g, _h; // size_t cause using Vector3.SquaredLength

	Node(bool solid, int id, Vector3 pos);
	~Node();
	void SetNodeAdjacent(Node* up, Node* down, Node* left, Node* right);
	bool GetSolid();
	void SetSolid(bool in);
	int GetNodeId();
	Vector3 GetPosition();
	void SetPosition(Vector3 pos);
	bool GetVisited();
	void SetVisited(bool in);
	bool GetClosed();
	void SetClosed(bool in);
	Node* GetLeft();
	Node* GetRight();
	Node* GetUp();
	Node* GetDown();
	Node* GetPrev();
	void SetPrev(Node* prev);

	void CalcFGH(Vector3 _start, Vector3 _dest); // A*
};

class TileMapComponent: public IComponent
{
//For Editor
	bool turnOnTileMap; //Bool to activate drawing in GraphicSystem to draw tiles.
	Vector3 _mapCenterOffset; // the map's local center offset from bottom left, use this when calculating offset
	Vector3 _tilesize; //x, y //tilesize will be calculated from scale in transformComponent.
					//Everytime Scaling changes, tilesize is recalculated.
	int _mapHeight, _mapWidth;

	typedef int tileNumber;
	std::unordered_map < tileNumber, Node* > _tileNodeMap; // <NodeId, NodePtr>
	tileNumber** _tilemapId; // 2dArray of the NodeMap in ID form

	int** _tilemapInput; // 2dArray of node solidity //For Serialisation and Deserialisation

	//TransformComponent* transCom;

public:

	TileMapComponent() : 
		_mapHeight{ 0 }, _mapWidth{ 0 }, _tilemapInput{ nullptr }, _tilesize{ 0, 0, 0 }, turnOnTileMap{ false }, _tileNodeMap{}
	{
		//if(GetParentPtr())
	}

	void Init() override
	{
		//transCom = (TransformComponent*)(GetSibilingComponent(ComponentId::CT_Transform));
	}


	TileMapComponent(const TileMapComponent& copy) = default;

	std::string ComponentName() const override
	{
		return "TileMapComponent";
	}


	void SerialiseComponent(Serialiser& document) override
	{
		if (document.HasMember("MapWidth") && document["MapWidth"].IsInt())
			_mapWidth = document["MapWidth"].GetInt();

		if (document.HasMember("MapHeight") && document["MapHeight"].IsInt())
			_mapHeight = document["MapHeight"].GetInt();


		if (document.HasMember("TileMap"))
		{
			_tilemapInput = new int * [_mapHeight];
			_tilemapId = new tileNumber * [_mapHeight];

			for (int height = 0; height < _mapHeight; height++)
			{
				_tilemapInput[height] = new int[_mapWidth];
				_tilemapId[height] = new tileNumber[_mapWidth];

				for (int width = 0; width < _mapWidth; width++)
				{
					_tilemapInput[height][width] = document["TileMap"][height * width + width].GetInt();
				}
			}
		}

	}



	void DeSerialiseComponent(DeSerialiser& prototypeDoc) override
	{
		rapidjson::Value value;

		value.SetBool(GetEnable());
		prototypeDoc.AddMember("TileMapComponent", value);

		value.SetInt(_mapHeight);
		prototypeDoc.AddMember("MapHeight", value);

		value.SetInt(_mapWidth);
		prototypeDoc.AddMember("MapWidth", value);

		value.SetArray();
		{
			for (size_t height = 0; height < _mapHeight; height++)
			{
				for (size_t width = 0; width < _mapWidth; width++)
				{
					value.PushBack(rapidjson::Value(_tilemapInput[height][width]).Move(), prototypeDoc.GetAllocator());
				}
			}
			prototypeDoc.AddMember("TileMap", value);
		}

	}

	void DeSerialiseComponent(rapidjson::Value& prototypeDoc, rapidjson::MemoryPoolAllocator<>& allocator)
	{
		rapidjson::Value value;

		value.SetBool(GetEnable());
		prototypeDoc.AddMember("TileMapComponent", value, allocator);

		//value.SetInt(_typeIdGraphic);
		//prototypeDoc.AddMember("G.TypeId", value);
		value.SetInt(_mapHeight);
		prototypeDoc.AddMember("MapHeight", value, allocator);

		value.SetInt(_mapWidth);
		prototypeDoc.AddMember("MapWidth", value, allocator);

		value.SetArray();
		{
			for (size_t height = 0; height < _mapHeight; height++)
			{
				for (size_t width = 0; width < _mapWidth; width++)
				{
					value.PushBack(rapidjson::Value(_tilemapInput[height][width]).Move(), allocator);
				}
			}
			prototypeDoc.AddMember("TileMap", value, allocator);
		}
	}



	void DeserialiseComponentSceneFile(IComponent* protoCom, rapidjson::Value& value, rapidjson::MemoryPoolAllocator<>& allocator) override
	{
		TileMapComponent* tileMapComponent = dynamic_cast<TileMapComponent*>(protoCom);

		if (!tileMapComponent)
		{
			DeSerialiseComponent(value, allocator);
			return;
		}

		rapidjson::Value enable;
		rapidjson::Value mapHeight;
		rapidjson::Value mapWidth;


		bool addComponentIntoSceneFile = false;

		if (tileMapComponent->GetEnable() != this->GetEnable())
		{
			addComponentIntoSceneFile = true;
			enable.SetBool(GetEnable());
		}

		if (tileMapComponent->_mapHeight != this->_mapHeight)
		{
			addComponentIntoSceneFile = true;
			mapHeight.SetBool(_mapHeight);
		}

		if (tileMapComponent->_mapWidth != this->_mapWidth)
		{
			addComponentIntoSceneFile = true;
			mapWidth.SetBool(_mapWidth);
		}

		//if (addComponentIntoSceneFile)	//If anyone of component data of obj is different from Prototype
		{
			if (!enable.IsNull())
				value.AddMember("TileMapComponent", enable, allocator);
			else
				value.AddMember("TileMapComponent", tileMapComponent->GetEnable(), allocator);

			if (!mapHeight.IsNull())	//if rapidjson::value container is not empty
			{
				value.AddMember("MapHeight", mapHeight, allocator);
			}

			if (!mapWidth.IsNull())	//if rapidjson::value container is not empty
			{
				value.AddMember("MapWidth", mapWidth, allocator);
			}

			//DeserialNodeMap();

			rapidjson::Value tilemap;
			tilemap.SetArray();
			{
				for (size_t height = 0; height < _mapHeight; height++)
				{
					for (size_t width = 0; width < _mapWidth; width++)
					{
						value.PushBack(rapidjson::Value(_tilemapInput[height][width]).Move(), allocator);
					}
				}
				value.AddMember("TileMap", tilemap, allocator);
			}
		}
	}


	void Inspect() override;

	bool GetTurnOnTileMap()
	{
		return turnOnTileMap;
	}

	TileMapComponent* CloneComponent()
	{
		return new TileMapComponent(*this);
	}

	//PaletteType** GetTileMap()
	//{
	//	return _tilemap;
	//}
	//std::unordered_map<size_t, std::string> GetPalette()
	//{
	//	return palette;
	//}
	//int GetHeight()
	//{
	//	return _height;
	//}
	//int GetWidth()
	//{
	//	return _width;
	//}
	//int GetTileSize()
	//{
	//	return _tilesize;
	//}


	void CalcTileSize();
	void CalcOffset();

	// remove the offset, cause that is just calculated during map build, and map resize
	void SerialNodeMap();
	//void DeserialNodeMap();
	void DeleteNodeMap();

	void ResizeNodeMap();
	void EditNodeMap(int newHeight, int newWidth);
	//void ToggleNodeSolidity(float x, float y);

// GetSet
	void SetMapHeight(int in);
	int GetMapHeight();
	void SetMapWidth(int in);
	int GetMapWidth();
	Vector3 GetTilesize();
	int** GetTilemapId();
	std::unordered_map < int, Node* > GetNodeMap();

	// have serial in serial out 
};

