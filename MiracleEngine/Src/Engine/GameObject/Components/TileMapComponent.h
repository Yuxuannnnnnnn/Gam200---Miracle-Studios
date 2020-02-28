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
	GameObject* _NodeObj;

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
	typedef std::string Image;
		
	//PaletteType** _tilemap;

	int _height, _width; //Results in the total number of tiles in the tilemap.

	Image onImage; //Image shows when tile is selected

	std::vector<int> selectedTiles; 

	Vector3 _tilesize; //x, y //tilesize will be calculated from scale in transformComponent.
						//Everytime Scaling changes, tilesize is recalculated.

	bool turnOnTileMap; //Bool to activate drawing in GraphicSystem to draw tiles.

	//Array of nodes. 

	Vector3 _tileSize; // TODO : replace with the one YX gonna push

	int _mapHeight, _mapWidth, _mapTileSize; // TODO : replace with the one YX gonna push 
	std::unordered_map < int, Node* > _tileNodeMap; // <NodeId, NodePtr>
	int** _tilemapInput; // 2dArray of the NodeMap in ID form

public:
	TileMapComponent() : _height{ 0 }, _width{ 0 }, _tilesize{ 0 }, _tilemap{ nullptr } {};
	TileMapComponent(const TileMapComponent& copy) = default;

	std::string ComponentName() const override
	{
		return "TileMapComponent";
	}
	void SerialiseComponent(Serialiser& document) override;
	void DeSerialiseComponent(DeSerialiser& prototypeDoc) override
	{

	}
	void DeSerialiseComponent_LevelFile(DeSerialiser& levelDoc) 
	{
		rapidjson::Value tileMapObject;
		tileMapObject.SetObject();
		{
			rapidjson::Value value;
			value.SetInt(_height);
			tileMapObject.AddMember("Height", value, levelDoc.Allocator());

			value.SetInt(_width);
			tileMapObject.AddMember("Width", value, levelDoc.Allocator());

			value.SetArray();
			{
				for (auto& palettePair : palette)
				{
					rapidjson::Value ArrayPair;
					ArrayPair.SetArray();
					ArrayPair.PushBack(rapidjson::Value(palettePair.first).Move(), levelDoc.Allocator());
					ArrayPair.PushBack(rapidjson::StringRef(palettePair.second.c_str()), levelDoc.Allocator());

					value.PushBack(ArrayPair, levelDoc.Allocator());
				}
				tileMapObject.AddMember("Palette", value, levelDoc.Allocator());
			}

			value.SetArray();
			{
				for (size_t height = 0; height < _height; height++)
				{
					for (size_t width = 0; width < _width; width++)
					{
						value.PushBack(rapidjson::StringRef(_tilemap[height][width].c_str()), levelDoc.Allocator());
					}
				}
				tileMapObject.AddMember("TileMap", value, levelDoc.Allocator());
			}
		}


		levelDoc["AllTileMaps"].PushBack(tileMapObject, levelDoc.Allocator());
	}
	void Inspect() override
	{
		//Add Palette button - when pressed new palette button will appear
		//Imgui::buttons for each palette type - when pressed, palette texture will appear, and can snap to position on screen 

		//Remove Palette button - must have textbox to remove all such tile
		ImGui::Spacing();
		ImGui::InputInt("height ", &_height);
		ImGui::Spacing();
		ImGui::InputInt("width ", &_width);
		ImGui::Spacing();
		ImGui::InputInt("tilesize ", &_tilesize);
	}
	void DeserialiseComponentSceneFile(IComponent* protoCom, rapidjson::Value& value, rapidjson::MemoryPoolAllocator<>& allocator) override { return; }

	TileMapComponent* CloneComponent()
	{
		return new TileMapComponent(*this);
	}

	PaletteType** GetTileMap()
	{
		return _tilemap;
	}

	std::unordered_map<size_t, std::string> GetPalette()
	{
		return palette;
	}

	int GetHeight()
	{
		return _height;
	}
	int GetWidth()
	{
		return _width;
	}
	int GetTileSize()
	{
		return _tilesize;
	}

	void CreateNodeMap(int w, int h);
	void EditNodeMap(Vector3 offset, Vector3 scaleset, int newHeight, int newWidth);
	void EditNodeMap(Vector3 offset, Vector3 scaleset);
	void ToggleNodeSolidity(float x, float y);
};

