#pragma once
#include "GameObject.h"
#include <string>



class BinaryMap
{
private:
	/*The number of horizontal elements*/
	int _mapWidth;

	/*The number of vertical elements*/
	int _mapHeight;


	int** MapData;	//All Objects

   /*collision data of the binary map.
   if an array element in MapData is 1, it represents a collision cell,
   any other value is a non-collision cell*/
	int** BinaryCollisionArray; //For Physics/Collision data


	int** LogicMap; //For Logic System/ AI scripts

public:

	BinaryMap(Serialiser& document)
	{
		if (document.HasMember("Width") && document["Width"].IsInt())
		{
			_mapWidth = document["Width"].IsInt();
		}


		if (document.HasMember("Height") && document["Height"].IsInt())
		{
			_mapHeight = document["Height"].IsInt();
		}


		MapData = new int*[_mapHeight];
		for (int i = 0; i < _mapHeight; i++)
		{
			MapData[i] = new int[_mapWidth];
		}


		//Check	for TileMap and whether it is an array
		if (document.HasMember("TileMap") && document["TileMap"].IsArray())	
		{
			//Loop through the TileMap IntArray By each Row
			for (int y = 0; y < _mapHeight; y++)
			{
				for (int x = 0; x < _mapWidth; x++)
				{
					//Check if individual elements are Integers
					if (document["TileMap"][y + x].IsInt())
					{
						MapData[y][x] = document["TileMap"][y + x].GetInt();


					}
				}
			}
		}



		const rapidjson::Value& Legend = document["Legend"];

		//Loop Through the Legend List in Rapid Json Document
		for (int i = 0; i < Legend.Size(); i++)
		{
			//Loop through the TypeIdGO list
			for (int count = 0; count < (int)TypeIdGO::COUNT; count++)
			{
				//Check if the Lengend list has the TypeIdGO string name
				if (Legend.HasMember(ToString((TypeIdGO)count)))
				{
					//Get the tileMapId of the particular Game Object
					int tileMapId = document[ToString((TypeIdGO)count)].GetInt();

				//Loop through the entire map to search for the tilemapId to replace with the TypeIdGO Enum
					for (int y = 0; y < _mapHeight; y++)
					{
						for (int x = 0; x < _mapWidth; x++)
						{
							if (MapData[y][x] == tileMapId)
							{
								MapData[y][x] = count;
							}
						}
					}

				}
			}
		}
	}




	int ImportMapDataFromFile(const char* FileName);
	void FreeMapData(void);

	void PrintRetrievedInformation(void);

	void SnapToCell(float* Coordinate);

	int CheckInstanceBinaryMapCollision(float PosX, float PosY,
		float scaleX, float scaleY);
};

