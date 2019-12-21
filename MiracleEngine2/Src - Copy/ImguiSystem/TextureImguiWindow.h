#pragma once



class TextureImguiWindow: public IBaseImguiWindow
{
	static Texture2D** _currTexture;

public:

	TextureImguiWindow(bool open = false,	//Set the settings for the imgui window
		ImGuiWindowFlags flags = ImGuiWindowFlags_::ImGuiWindowFlags_MenuBar)
		:IBaseImguiWindow("Texture", 60, 60, 276, 328, open, flags)
	{
	}

	void Update() override
	{
	    //ImGui::Image(*_currTexture, ImVec2((*_currTexture)->GetWidth(), (*_currTexture)->GetHeight()),
		//	ImVec2(0, 0), ImVec2(1, 1), ImVec4(1.0f, 1.0f, 1.0f, 1.0f), ImVec4(1.0f, 1.0f, 1.0f, 0.5f));
	}

	static void setTexture(TextureImguiWindow* window, Texture2D* texture, std::string name)
	{
		name += " Texture";
		window->SetWindowTrue();
		window->SetName(name.c_str());
		_currTexture = &texture;
	}
};



