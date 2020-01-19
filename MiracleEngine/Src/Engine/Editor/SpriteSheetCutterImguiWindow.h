#pragma once
#include "Tools/Resource/ResourceSystem.h"




class SpriteSheetCutterImguiWindow: public IBaseImguiWindow
{
	static Texture2D* _currTexture;
	static std::string _textureName;

	int _frames, _columns, _rows;
public:

	SpriteSheetCutterImguiWindow(bool open = false,	//Set the settings for the imgui window
		ImGuiWindowFlags flags = ImGuiWindowFlags_::ImGuiWindowFlags_MenuBar)
		:IBaseImguiWindow("SpriteSheet Cutter  ", 250, 60, 300, 300, open, flags, ImGuiCond_Once), 
		_frames{ 0 }, _columns{ 0 }, _rows{0}
	{
	}


	void Update() override;


	static void OpenSpriteSheetCutterWindow(SpriteSheetCutterImguiWindow* window, Texture2D* texture, std::string name)
	{
		_textureName = name;
		name += " SpriteSheet Cutter";
		window->SetWindowTrue();
		window->SetName(name.c_str());
		_currTexture = texture;
	}


	void GenerateSpriteSheetData(std::string filename)
	{
		//size_t namesize = _textureName.find_last_of(".png") - 4 - path.find_last_of("\\/");

		DeSerialiser SpriteSheetData(filename);

		rapidjson::Value value;
		value.SetString(rapidjson::StringRef(_textureName.c_str()));
		SpriteSheetData.AddMember("SpriteSheetName", value);
		value.SetInt(_frames);
		SpriteSheetData.AddMember("NoofFrames", value);

		//Get Texture Height and Width Resolution
		//float Height = _currTexture->GetHeight();
		//float Width = _currTexture->GetWidth();

	//Interval height and width
		float ColumnInterval = 1.0f / (float)(_columns);
		float RowInterval = 1.0f / (float)(_rows);

	//Calculate U0, V0 and U1, V1 for each frame
		for (int i = 0; i < _frames; i++)
		{
			int row;
			int column;
			if (_columns)
			{
				row = i / _columns; //row is from 0	
				column = i % _columns;//column is from 0		
			}
			else
			{
				break;
			}

			float u0, v0, u1, v1;

			rapidjson::Value value;
			u0 = ColumnInterval * column;
			v0 = RowInterval * (_rows - row - 1);
			u1 = ColumnInterval * (column + 1);
			v1 = RowInterval * (_rows - row);
			
			rapidjson::Value Array;
			Array.SetArray();
			value.SetFloat(u0);
			Array.PushBack(value, SpriteSheetData.GetAllocator());
			value.SetFloat(v0);
			Array.PushBack(value, SpriteSheetData.GetAllocator());			
			value.SetFloat(u1);
			Array.PushBack(value, SpriteSheetData.GetAllocator());
			value.SetFloat(v1);
			Array.PushBack(value, SpriteSheetData.GetAllocator());


			std::string frameNumber = std::to_string(i);
			SpriteSheetData.AddMember(frameNumber, Array);
		}

		SpriteSheetData.~DeSerialiser();


		std::string file = filename.substr(filename.find_last_of("\\/") + 1);

		MyResourceSystem.AddNewAnimationResource(std::pair<std::string, std::string>(file, filename));
	}
};

