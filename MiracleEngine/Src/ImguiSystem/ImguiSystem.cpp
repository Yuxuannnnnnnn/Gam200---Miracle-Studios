#include "PrecompiledHeaders.h"
#include "ImguiSystem.h"



ImguiSystem::ImguiSystem()
	:clear_color{ ImVec4(0.0f, 0.0f, 0.0f, 0.0f) }
{
}


void ImguiSystem::Init(const WindowsSystem& window)
{

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();  (void)io;


	ImGui_ImplWin32_Init(window.Get_hwnd()); 	//Init Win32

	//Init OpenGL Imgui Implementation
	// GL 3.0 + GLSL 130
	const char* glsl_version = "#version 130";
	ImGui_ImplOpenGL3_Init(glsl_version);

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();

}


void ImguiSystem::UpdateFrame()
{
	// Start the Dear ImGui frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
}


void ImguiSystem::Render()
{
	ImGui::Render(); // Rendering


	//Clear opengl buffer
	glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
	glClear(GL_COLOR_BUFFER_BIT);


	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData()); // Rendering
}




ImguiSystem::~ImguiSystem()
{
	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}
