#include "PrecompiledHeaders.h"
#include "ImguiSystem.h"



ImguiSystem::ImguiSystem(const Window& window)
	:_window{ window }, clear_color{ ImVec4(0.0f, 0.0f, 0.0f, 0.0f) }, _pause{ false }
{
	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;// Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable; // Enable Docking
	//io.ConfigFlags |= ImGuiWindowFlags_MenuBar; 
	io.WantCaptureKeyboard = true;
	//io.ConfigDockingWithShift = true;
	//io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable; //Enable Multi - Viewport / Platform Windows

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();

	// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
	//ImGuiStyle& style = ImGui::GetStyle();
	//if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	//{
	//	style.WindowRounding = 0.0f;
	//	style.Colors[ImGuiCol_WindowBg].w = 1.0f;
	//}

	ImGui_ImplWin32_Init(_window.Get_hwnd() ,_window.Get_m_wglDC()); 	//Init Win32

	//Init OpenGL Imgui Implementation
	// GL 3.0 + GLSL 130
	const char* glsl_version = "#version 130";
	ImGui_ImplOpenGL3_Init(glsl_version);

	IM_ASSERT(ImGui::GetCurrentContext() != NULL && "Missing dear imgui context. Refer to examples app!"); // Exceptionally add an extra assert here for people confused with initial dear imgui setup


	//New All ImguiWindows
	
	_ImguiWindows[static_cast<int>(ImguiWindows::HIERARCHY)] = new HierarchyImguiWindow();
	_ImguiWindows[static_cast<int>(ImguiWindows::INSPECTOR)] = new InspectionImguiWindow();
	_ImguiWindows[static_cast<int>(ImguiWindows::PREFAB_FOLDER)] = new PreFabImguiWindow();
	/*
	_ImguiWindows[ImguiWindows::SCENE] = new Scene();
	*/
}


//Imgui must save file
void ImguiSystem::UpdateFrame()
{
	ImGui_ImplOpenGL3_NewFrame();	// Start the Dear ImGui frame
	ImGui_ImplWin32_NewFrame();		//
	ImGui::NewFrame();				///

	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File  "))
		{
			ImGui::Spacing();
			if (ImGui::BeginMenu("Load  "))
			{
				if (ImGui::MenuItem("./Resources/TextFiles/States/TestLevel.txt"))
				{
					EngineSystems::GetInstance()._gameObjectFactory->DeleteLevel();
					EngineSystems::GetInstance()._gameObjectFactory->FileRead_Level("./Resources/TextFiles/States/TestLevel.txt");
				}
				ImGui::EndMenu();
			}
			ImGui::Spacing();
			if (ImGui::MenuItem("Save   "))
			{

			}
			ImGui::Spacing();
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Edit  "))
		{
			//if (ImGui::MenuItem("Undo", "CTRL+Z")) {}
			//if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) {}  // Disabled item
			//ImGui::Separator();
			//if (ImGui::MenuItem("Cut", "CTRL+X")) {}
			//if (ImGui::MenuItem("Copy", "CTRL+C")) {}
			//if (ImGui::MenuItem("Paste", "CTRL+V")) {}

			ImGui::EndMenu();
		}
		if(ImGui::BeginMenu("Game Settings  "))
		{
			if (ImGui::MenuItem("Pause  ")) 
			{
				_pause = 1;
			}
			//ImGui::Separator();
			if (ImGui::MenuItem("Play  "))
			{
				_pause = 0;
			}
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}




		for (int i = 0; i < (int)ImguiWindows::COUNT; i++)	//Update all Imgui Windows
		{
			if (_ImguiWindows[i]->GetOpen()) //if false, window will not be created
			{
				// Start of Main window body.
				if (!ImGui::Begin(_ImguiWindows[i]->GetName(), &(_ImguiWindows[i]->GetOpen()), _ImguiWindows[i]->GetFlags()))
				{
					ImGui::End();	// Early out if the window is collapsed, as an optimization.
					continue;
				}

				_ImguiWindows[i]->Update(); //Update the contents of each window

				ImGui::End();									//End of window body
			}
		}

}


void ImguiSystem::Render()
{


	//Clear opengl buffer - graphic will clear, otherwise wont render
	/*glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
	glClear(GL_COLOR_BUFFER_BIT);*/

	ImGui::Render(); // Rendering

	
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	//glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);

	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData()); // Rendering


	// Update and Render additional Platform Windows
	//if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	//{
	//		HDC backup_current_context = GetDC(_window.Get_hwnd());
	//		ImGui::UpdatePlatformWindows();
	//		ImGui::RenderPlatformWindowsDefault();
	//		//wglMakeCurrent(backup_current_context, _window.Get_m_wglDC());
	//}
}




ImguiSystem::~ImguiSystem()
{
	// Cleanup


	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}