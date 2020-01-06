#pragma once
#include "SpriteSheetCutterImguiWindow.h"
#include "Tools/Resource/ResourceManager.h"
#include "GlobalContainer.h"



class TextureImguiWindow: public IBaseImguiWindow
{
	static Texture2D* _currTexture;
	static std::string _textureName;

public:

	TextureImguiWindow(bool open = false,	//Set the settings for the imgui window
		ImGuiWindowFlags flags = ImGuiWindowFlags_::ImGuiWindowFlags_MenuBar)
		:IBaseImguiWindow("Texture", 250, 60, 1000, 900, open, flags, ImGuiCond_Once)
	{
	}

	void Update() override;

	static void setTexture(TextureImguiWindow* window, Texture2D* texture, std::string name)
	{
		_textureName = name;
		name += " Texture";
		window->SetWindowTrue();
		window->SetName(name.c_str());
		_currTexture = texture;
	}
};



