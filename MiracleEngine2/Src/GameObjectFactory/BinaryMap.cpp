#include "PrecompiledHeaders.h"
#include "BinaryMap.h"
//
//
//
//
///******************************************************************************/
///*!
//	This function opens the file name "FileName" and retrieves all the map data.
//	It allocates memory for the 2 arrays: MapData & BinaryCollisionArray
//	The first line in this file is the width of the map.
//	The second line in this file is the height of the map.
//	The remaining part of the file is a series of numbers
//	Each number represents the ID (or value) of a different element in the
//	double dimensionaly array.
//
//	Example:
//
//	Width 5
//	Height 5
//	1 1 1 1 1
//	1 1 1 3 1
//	1 4 2 0 1
//	1 0 0 0 1
//	1 1 1 1 1
//
//
//	After importing the above data, "MapData" and " BinaryCollisionArray"
//	should be
//
//	1 1 1 1 1
//	1 1 1 3 1
//	1 4 2 0 1
//	1 0 0 0 1
//	1 1 1 1 1
//
//	and
//
//	1 1 1 1 1
//	1 1 1 0 1
//	1 0 0 0 1
//	1 0 0 0 1
//	1 1 1 1 1
//
//	respectively.
//
//	Finally, the function returns 1 if the file named "FileName" exists,
//	otherwise it returns 0
// */
// /*****************************************************************************/
//int BinaryMap::ImportMapDataFromFile(const char* FileName)
//{
//	FILE* file;															  //Use Rapid Json
//	//open file, and let file ptr point to the file							  //
//	fopen_s(&file, FileName, "r");											  //
//																			  //
//	if (!file)//if file does not exist, return 0							  //
//		return 0;															  //
//																			  //
//	fscanf_s(file, "Width %d\n", &BINARY_MAP_WIDTH);//save width 			  //
//	fscanf_s(file, "Height %d\n", &BINARY_MAP_HEIGHT);//save height			  //
//
//
//
//
//
//
//
//
//
//
//
//	//Allocate double array memory to MapData
//	MapData = new int* [BINARY_MAP_HEIGHT];
//	for (int i = 0; i < BINARY_MAP_HEIGHT; i++)
//	{
//		MapData[i] = new int[BINARY_MAP_WIDTH];
//	}
//
//
//	//Reads in data from file into MapData
//	for (int height = 0; height < BINARY_MAP_HEIGHT; height++)
//	{
//		for (int width = 0; width < BINARY_MAP_WIDTH; width++)
//		{
//			fscanf_s(file, "%d", &MapData[height][width]);
//		}
//	}
//
//
//	//Allocates double array memory to BinaryCollisionArray
//	BinaryCollisionArray = new int* [BINARY_MAP_HEIGHT];
//	for (int i = 0; i < BINARY_MAP_HEIGHT; i++)
//	{
//		BinaryCollisionArray[i] = new int[BINARY_MAP_WIDTH];
//	}
//
//	//Converts data from MapData into Collision Format and 
//	//saves in BinaryCollisionArray
//	for (int height = 0; height < BINARY_MAP_HEIGHT; height++)
//	{
//		for (int width = 0; width < BINARY_MAP_WIDTH; width++)
//		{
//			BinaryCollisionArray[height][width]
//				= MapData[height][width] == 1 ? 1 : 0;
//		}
//	}
//
//	fclose(file);
//	return 1;
//}
//
//
//
//
///******************************************************************************/
///*!
//	This function frees the memory that was allocated for the 2 arrays MapData
//	& BinaryCollisionArray which was allocated in the "ImportMapDataFromFile"
//	function
// */
// /*****************************************************************************/
//void BinaryMap::FreeMapData(void)
//{
//	//delete internal arrays
//	for (int height = 0; height < BINARY_MAP_HEIGHT; height++)
//	{
//		delete[] MapData[height];
//		delete[] BinaryCollisionArray[height];
//	}
//
//	delete[]MapData;//delete external array
//	delete[]BinaryCollisionArray;
//}
//
//
//
//
///******************************************************************************/
///*!
//	This function prints out the content of the 2D array “MapData”
//	Add spaces and end lines at convenient places
// */
// /*****************************************************************************/
//void BinaryMap::PrintRetrievedInformation(void)
//{
//	//Print out the numbers from MapData
//	for (int height = 0; height < BINARY_MAP_HEIGHT; height++)
//	{
//		for (int width = 0; width < BINARY_MAP_WIDTH; width++)
//		{
//			std::cout << MapData[height][width] << " ";
//		}
//		std::cout << std::endl;
//	}
//}
//
//
//
//
///******************************************************************************/
///*!
//	This function retrieves the value of the element (X;Y)
//	in BinaryCollisionArray.
//	Before retrieving the value, it should check that the
//	supplied X and Y values
//	are not out of bounds (in that case return 0)
// */
// /*****************************************************************************/
//int BinaryMap::GetCellValue(int X, int Y)
//{
//	if (X >= BINARY_MAP_WIDTH || X < 0) //Check X
//	{
//		return 0;
//	}
//
//	if (Y >= BINARY_MAP_HEIGHT || Y < 0) //Check Y 
//	{
//		return 0;
//	}
//
//	return BinaryCollisionArray[Y][X]; // return the cell value
//}
//
//
//
//
///******************************************************************************/
///*!
//	This function snaps the value sent as parameter to the center of the cell.
//	It is used when a sprite is colliding with a collision area from one
//	or more side.
//	To snap the value sent by "Coordinate", find its integral part by type
//	casting it to an integer, then add 0.5 (which is half the cell's width
//	or height)
// */
// /*****************************************************************************/
//void BinaryMap::SnapToCell(float* Coordinate)
//{
//	*Coordinate = (int)* Coordinate + 0.5f;
//}
//
//
//
//
//
///*****************************************************************************/
///*!
//	This function creates 2 hot spots on each side of the object instance,
//	and checks if each of these hot spots is in a collision area (which means
//	the cell if falls in has a value of 1).
//	At the beginning of the function, a "Flag" integer should be initialized to
//	0.
//	Each time a hot spot is in a collision area, its corresponding bit
//	in "Flag" is set to 1.
//	Finally, the function returns the integer "Flag"
//	The position of the object instance is received as PosX and PosY
//	The size of the object instance is received as scaleX and scaleY
//
//	Note: This function assume the object instance's size is 1 by 1
//		  (the size of 1 tile)
//
//	Creating the hotspots:
//		-Handle each side separately.
//		-2 hot spots are needed for each collision side.
//		-These 2 hot spots should be positioned on 1/4 above the center
//		and 1/4 below the center
//
//	Example: Finding the hots spots on the left side of the object instance
//
//	float x1, y1, x2, y2;
//
//	-hotspot 1
//	x1 = PosX + scaleX/2    To reach the right side
//	y1 = PosY + scaleY/4    To go up 1/4 of the height
//
//	-hotspot 2
//	x2 = PosX + scaleX/2    To reach the right side
//	y2 = PosY - scaleY/4    To go down 1/4 of the height
// */
// /****************************************************************************/
//int CheckInstanceBinaryMapCollision(float PosX, float PosY,
//	float scaleX, float scaleY)
//{
//	int Flag = 0; //Flag to show that a hotspot has collided with a solid cell
//	float Right_up_x = PosX + scaleX / 2;
//	float Right_up_y = PosY + scaleY / 4;
//	float Right_down_x = PosX + scaleX / 2;
//	float Right_down_y = PosY - scaleY / 4;
//
//	float Left_up_x = PosX - scaleX / 2;
//	float Left_up_y = PosY + scaleY / 4;
//	float Left_down_x = PosX - scaleX / 2;
//	float Left_down_y = PosY - scaleY / 4;
//
//	float up_left_x = PosX - scaleX / 4;
//	float up_left_y = PosY + scaleY / 2;
//	float up_right_x = PosX + scaleX / 4;
//	float up_right_y = PosY + scaleY / 2;
//
//	float down_right_x = PosX + scaleX / 4;
//	float down_right_y = PosY - scaleY / 2;
//	float down_Left_x = PosX - scaleX / 4;
//	float down_Left_y = PosY - scaleY / 2;
//
//	//Checks for Right hotspots
//	if (BinaryCollisionArray[(int)Right_up_y][(int)Right_up_x] == 1
//		|| BinaryCollisionArray[(int)Right_down_y][(int)Right_down_x] == 1)
//	{
//		Flag += COLLISION_RIGHT;
//	}
//
//	//Checks for Left hotspots
//	if (BinaryCollisionArray[(int)Left_up_y][(int)Left_up_x] == 1
//		|| BinaryCollisionArray[(int)Left_down_y][(int)Left_down_x] == 1)
//	{
//		Flag += COLLISION_LEFT;
//	}
//
//	//Check for Top Hotspots
//	if (BinaryCollisionArray[(int)up_left_y][(int)up_left_x] == 1
//		|| BinaryCollisionArray[(int)up_right_y][(int)up_right_x] == 1)
//	{
//		Flag += COLLISION_TOP;
//	}
//
//	//Check for Bottom Hotspots
//	if (BinaryCollisionArray[(int)down_right_y][(int)down_right_x] == 1
//		|| BinaryCollisionArray[(int)down_Left_y][(int)down_Left_x] == 1)
//	{
//		Flag += COLLISION_BOTTOM;
//	}
//
//
//	return Flag;
//}
