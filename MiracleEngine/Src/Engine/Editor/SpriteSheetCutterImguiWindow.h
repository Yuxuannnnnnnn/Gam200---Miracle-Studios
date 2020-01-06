#pragma once




class SpriteSheetCutterImguiWindow: public IBaseImguiWindow
{
	static Texture2D* _currTexture;
	static std::string _textureName;

	int _frames, _columns, _rows;
public:

	SpriteSheetCutterImguiWindow(bool open = false,	//Set the settings for the imgui window
		ImGuiWindowFlags flags = ImGuiWindowFlags_::ImGuiWindowFlags_MenuBar)
		:IBaseImguiWindow("SpriteSheet Cutter  ", 250, 60, 300, 300, open, flags, ImGuiCond_Once)
	{
	}


	void Update() override
	{
		//No. of frames
		//Columns
		//Rows
		//Generate SpriteSheet
		ImGui::Spacing();
		ImGui::InputInt("No. of Frames ", &_frames);
		ImGui::Spacing();
		ImGui::InputInt("Columns ", &_columns);
		ImGui::Spacing();
		ImGui::InputInt("Rows ", &_rows);

		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::Spacing();

		if (ImGui::Button("Generate SpriteSheet Data File   "))
		{
			GenerateSpriteSheetData();
		}
	}

	static void OpenSpriteSheetCutterWindow(SpriteSheetCutterImguiWindow* window, Texture2D* texture, std::string name)
	{
		name += " SpriteSheet Cutter";
		window->SetWindowTrue();
		window->SetName(name.c_str());
		_currTexture = texture;
		_textureName = name;
	}


	void GenerateSpriteSheetData()
	{
		//size_t namesize = _textureName.find_last_of(".png") - 4 - path.find_last_of("\\/");
		size_t position = _textureName.find_last_of(".png");
		std::string fileName = _textureName.substr(position);
		fileName += "SpriteSheetData";
		fileName +=".json";
		DeSerialiser SpriteSheetData(fileName);

		rapidjson::Value value;
		value.SetString(rapidjson::StringRef(_textureName.c_str()));
		SpriteSheetData.AddMember("SpriteSheetName", value);
		value.SetInt(_frames);
		SpriteSheetData.AddMember("NoofFrames", value);

	//Get Texture Height and Width Resolution
		float Height = _currTexture->GetHeight();
		float Width = _currTexture->GetWidth();

	//Interval height and width
		float ColumnInterval = Width / (float)(_columns);
		float RowInterval = Height / (float)(_rows);

	//Calculate U0, V0 and U1, V1 for each frame
		for (int i = 0; i < _frames; i++)
		{
			int row = i / _columns; //row is from 0			
			int column = i % _columns;//column is from 0		

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
	}
};

