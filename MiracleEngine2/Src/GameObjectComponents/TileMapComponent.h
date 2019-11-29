#pragma once






class TileMapComponent: public IComponentSystem
{
	typedef std::string PaletteType;
		
	PaletteType** _tilemap;

	size_t _height;
	size_t _width;

	std::unordered_map<size_t, std::string> palette;

public:
	TileMapComponent() = default;
	TileMapComponent(const TileMapComponent& copy) = default;

	std::string ComponentName() const override
	{
		return "TileMapComponent";
	}

	void SerialiseComponent(Serialiser& document)	//Empty
	{
	}

	void SerialiseComponentFromLevelFile(rapidjson::Value& document)
	{
		if (document.HasMember("Width"))
		{
			_width = document["Width"].GetInt();
		}

		if (document.HasMember("Height"))
		{
			_height = document["Height"].GetInt();
		}

		if (document.HasMember("Palette"))
		{
			for (int i = 0; i < document["Palette"].Size(); i++)
			{
				palette[document["Palette"][i][1].GetInt()] = document["Palette"][i][2].GetString();
			}
		}
		
		if (document.HasMember("Palette"))
		{
			_tilemap = new PaletteType * [_height];

			for (size_t height = 0; height < _height; height++)
			{
				_tilemap[height] = new PaletteType[_width];

				for (size_t width = 0; width < _width; width++)
				{
					_tilemap[height][width] = palette[document["TileMap"][height * width + width].GetInt()];
				}
			}
		}

	}

	void DeSerialiseComponent(DeSerialiser& levelDoc) override
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
	}


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


};

