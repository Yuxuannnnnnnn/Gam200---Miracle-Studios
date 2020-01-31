#include "PrecompiledHeaders.h"
#include "SpriteSheetCutterImguiWindow.h"


Texture2D* SpriteSheetCutterImguiWindow::_currTexture = nullptr;
std::string SpriteSheetCutterImguiWindow::_textureName = "";

void SpriteSheetCutterImguiWindow::Update()
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
	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::Spacing();

	if (ImGui::Button("Generate SpriteSheet Data File"))
	{
		OPENFILENAME ofn = { sizeof ofn };
		ZeroMemory(&ofn, sizeof(ofn));
		ofn.lStructSize = sizeof(ofn);
		ofn.hwndOwner = _engineSystems._windowSystem->getWindow().Get_hwnd();

		char file[1024] = "\0";
		std::string texturename = _textureName.substr(0, _textureName.find_last_of("."));
		std::string fileName = texturename + "SpriteSheetData";
		strncpy(file, fileName.c_str(), fileName.size());
		ofn.lpstrFile = file;
		ofn.nMaxFile = 1024;
		ofn.Flags = OFN_ALLOWMULTISELECT | OFN_EXPLORER | OFN_NOCHANGEDIR;

		ofn.lpstrFilter = ".json\0.json";
		ofn.lpstrFileTitle = NULL;
		ofn.nMaxFileTitle = 0;

		WCHAR path[500];
		DWORD size = GetModuleFileNameW(NULL, path, 500);

		_bstr_t b(path);
		const char* c = b;

		ofn.lpstrInitialDir = "./Resources/TextFiles/AnimationData";
		ofn.nFilterIndex = 1;
		ofn.lpstrTitle = TEXT("Save SpriteSheet Data File");
		ofn.lpstrDefExt = "rle";

		if (GetSaveFileName(&ofn)) //If the user specifies a file nameand clicks the OK buttonand the function is successful, the return value is nonzero.
		{
			GenerateSpriteSheetData(ofn.lpstrFile);
		}

	}
}