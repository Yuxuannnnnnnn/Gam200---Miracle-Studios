#pragma once



class TextureImguiWindow: public IBaseImguiWindow
{
	static Texture2D* _currTexture;

public:

	TextureImguiWindow(bool open = false,	//Set the settings for the imgui window
		ImGuiWindowFlags flags = ImGuiWindowFlags_::ImGuiWindowFlags_MenuBar)
		:IBaseImguiWindow("Texture", 250, 60, 1000, 900, open, flags, ImGuiCond_Once)
	{
	}

	void Update() override
	{
		float width = _currTexture->GetWidth();
		float height = _currTexture->GetHeight();

		 float scaleW = width/900.0f;
		 float scaleH = height/800.0f;

		 float scale;
		 
		if (scaleW > scaleH)
		{
			scale = scaleW;
		}
		else
		{
			scale = scaleH;
		}

	    ImGui::Image((void*)(intptr_t)(_currTexture)->GetTextureID(), ImVec2(width/scale, height/scale),
		ImVec2(0, 0), ImVec2(1, 1), ImVec4(1.0f, 1.0f, 1.0f, 1.0f), ImVec4(1.0f, 1.0f, 1.0f, 0.5f));
	}

	static void setTexture(TextureImguiWindow* window, Texture2D* texture, std::string name)
	{
		name += " Texture";
		window->SetWindowTrue();
		window->SetName(name.c_str());
		_currTexture = texture;
	}
};



