#include "PrecompiledHeaders.h"
#include "TextureImguiWindow.h"

Texture2D* TextureImguiWindow::_currTexture = nullptr;
std::string TextureImguiWindow::_textureName = "";


void TextureImguiWindow::Update()
{

	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("Texture Settings  "))
		{
			if (ImGui::MenuItem("SpriteSheet Cutter  "))
			{
				SpriteSheetCutterImguiWindow* SpriteSheetCutterWindow = dynamic_cast<SpriteSheetCutterImguiWindow*>(_engineSystems._imguiSystem->GetWindows()["SpriteSheetCutter"]);
				SpriteSheetCutterImguiWindow::OpenSpriteSheetCutterWindow(SpriteSheetCutterWindow, _currTexture, _textureName);
			}           
			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}
	float width = _currTexture->GetWidth();
	float height = _currTexture->GetHeight();

	float scaleW = width / 900.0f;
	float scaleH = height / 800.0f;

	float scale;

	if (scaleW > scaleH)
	{
		scale = scaleW;
	}
	else
	{
		scale = scaleH;
	}


	std::unordered_map<std::string, Texture2D*>& textureMap= MyResourceSystem.GetTexture2DMap();

	//for (auto& texture : textureMap)
	//{
	//	ImGui::SetCursorPos(ImVec2((MyWindowsSystem.getWindow().GetWindowWidth() - (width / scale)) * 0.5f, (MyWindowsSystem.getWindow().GetWindowHeight() - (height / scale)) * 0.5f));
	//	ImGui::Image((void*)(intptr_t)(texture.second)->GetTextureID(), ImVec2(width / scale, height / scale),
	//		ImVec2(0, 0), ImVec2(1, 1), ImVec4(1.0f, 1.0f, 1.0f, 1.0f), ImVec4(1.0f, 1.0f, 1.0f, 0.5f));
	//}
	//
	//ImGui::SetCursorPos(ImVec2((MyWindowsSystem.getWindow().GetWindowWidth() - (width / scale)) * 0.5f, (MyWindowsSystem.getWindow().GetWindowHeight() - (height / scale)) * 0.5f));
	ImGui::Image((void*)(intptr_t)(_currTexture)->GetTextureID(), ImVec2(width / scale, height / scale),
		ImVec2(0, 0), ImVec2(1, 1), ImVec4(1.0f, 1.0f, 1.0f, 1.0f), ImVec4(1.0f, 1.0f, 1.0f, 0.5f));
}
