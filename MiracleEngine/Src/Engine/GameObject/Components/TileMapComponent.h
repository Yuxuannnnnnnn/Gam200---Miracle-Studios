#pragma once
#include "GameObject/IComponent.h"



class TileMapComponent: public IComponent
{
	typedef std::string PaletteType;
		
	PaletteType** _tilemap;
	std::unordered_map<size_t, std::string> palette;



	int _height, _width;


	Vector3 _tilesize; //x, y 

	std::string onImage;
	std::string offImage;






public:
	TileMapComponent() : _height{ 0 }, _width{ 0 }, _tilemap{ nullptr } {};
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
};

