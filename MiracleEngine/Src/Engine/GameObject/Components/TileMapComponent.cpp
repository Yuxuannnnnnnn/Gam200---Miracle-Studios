#include "PrecompiledHeaders.h"
#include "TileMapComponent.h"

void TileMapComponent::SerialiseComponent(Serialiser& document)
{
	if (document.HasMember("Width") && document["Width"].IsInt())
		_width = document["Width"].GetInt();

	if (document.HasMember("Height") && document["Width"].IsInt())
		_height = document["Height"].GetInt();

	if (document.HasMember("TileSize") && document["Width"].IsInt())
		_tilesize = document["TileSize"].GetInt();

	if (document.HasMember("Palette"))
	{
		for (unsigned i = 0; i < document["Palette"].Size(); i++)
		{
			palette[document["Palette"][i][0].GetInt()] = document["Palette"][i][1].GetString();
		}
	}

	if (document.HasMember("Palette"))
	{
		_tilemap = new PaletteType * [_height];

		for (int height = 0; height < _height; height++)
		{
			_tilemap[height] = new PaletteType[_width];

			for (int width = 0; width < _width; width++)
			{
				_tilemap[height][width] = palette[document["TileMap"][height * width + width].GetInt()];
			}
		}
	}

}
