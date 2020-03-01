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

	tileNumber** _tilemapInput; // 2dArray of the NodeMap in ID form


public:


	TileMapComponent() : 
		_mapHeight{ 0 }, _mapWidth{ 0 }, _tilemapInput{ nullptr }, _tilesize{ 0, 0, 0 }, turnOnTileMap{ false }, _tileNodeMap{}
	{}


	TileMapComponent(const TileMapComponent& copy) = default;

	std::string ComponentName() const override
	{
		return "TileMapComponent";
	}


	void SerialiseComponent(Serialiser& document) override
	{
		if (document.HasMember("Width") && document["Width"].IsInt())
			_mapWidth = document["Width"].GetInt();

		if (document.HasMember("Height") && document["Height"].IsInt())
			_mapHeight = document["Height"].GetInt();


		if (document.HasMember("TileMap"))
		{
			_tilemapInput = new tileNumber * [_mapHeight];

			for (int height = 0; height < _mapHeight; height++)
			{
				_tilemapInput[height] = new tileNumber[_mapWidth];

				for (int width = 0; width < _mapWidth; width++)
				{
					_tilemapInput[height][width] = document["TileMap"][height * width + width].GetInt();
				}
			}
		}

		CreateNodeMap(_mapWidth, _mapHeight, );
	}

	void DeSerialiseComponent(DeSerialiser& prototypeDoc) override
	{

	}


	void DeSerialiseComponent_LevelFile(DeSerialiser& levelDoc) 
	{
		rapidjson::Value tileMapObject;
		tileMapObject.SetObject();
		{
			rapidjson::Value value;
			value.SetInt(_mapHeight);
			tileMapObject.AddMember("Height", value, levelDoc.Allocator());

			value.SetInt(_mapWidth);
			tileMapObject.AddMember("Width", value, levelDoc.Allocator());

			//value.SetArray();
			//{
			//	for (auto& palettePair : palette)
			//	{
			//		rapidjson::Value ArrayPair;
			//		ArrayPair.SetArray();
			//		ArrayPair.PushBack(rapidjson::Value(palettePair.first).Move(), levelDoc.Allocator());
			//		ArrayPair.PushBack(rapidjson::StringRef(palettePair.second.c_str()), levelDoc.Allocator());

			//		value.PushBack(ArrayPair, levelDoc.Allocator());
			//	}
			//	tileMapObject.AddMember("Palette", value, levelDoc.Allocator());
			//}

			value.SetArray();
			{
				for (size_t height = 0; height < _mapHeight; height++)
				{
					for (size_t width = 0; width < _mapWidth; width++)
					{
						//value.PushBack(rapidjson::StringRef(_tilemap[height][width].c_str()), levelDoc.Allocator());
					}
				}
				tileMapObject.AddMember("TileMap", value, levelDoc.Allocator());
			}
		}


		levelDoc["AllTileMaps"].PushBack(tileMapObject, levelDoc.Allocator());
	}

	void DeserialiseComponentSceneFile(IComponent* protoCom, rapidjson::Value& value, rapidjson::MemoryPoolAllocator<>& allocator) override 
	{ return; }


	void Inspect() override
	{ 
		ImGui::Spacing();
		ImGui::InputInt("Height ", &_mapHeight);
		ImGui::Spacing();
		ImGui::InputInt("Width ", &_mapWidth);
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
	void DeserialNodeMap();
	void DeleteNodeMap();

	void ResizeNodeMap(Vector3 newScale);
	void EditNodeMap(int newHeight, int newWidth);
	void ToggleNodeSolidity(float x, float y);

	// have serial in serial out 
};

