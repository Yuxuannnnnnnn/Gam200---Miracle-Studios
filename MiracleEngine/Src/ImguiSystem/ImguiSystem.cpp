#include "PrecompiledHeaders.h"
#include "ImguiSystem.h"



ImguiSystem::ImguiSystem(const Window& window)
	:_window{ window }, clear_color{ ImVec4(0.0f, 0.0f, 0.0f, 0.0f) }
{
	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;// Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable; // Enable Docking
	io.ConfigDockingWithShift = true;
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

	ImGui_ImplWin32_Init(_window.Get_hwnd() /*,_window.Get_m_wglDC()*/); 	//Init Win32

	//Init OpenGL Imgui Implementation
	// GL 3.0 + GLSL 130
	const char* glsl_version = "#version 130";
	ImGui_ImplOpenGL3_Init(glsl_version);

	IM_ASSERT(ImGui::GetCurrentContext() != NULL && "Missing dear imgui context. Refer to examples app!"); // Exceptionally add an extra assert here for people confused with initial dear imgui setup

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


	//Clear opengl buffer - graphic will clear, otherwise wont render
	/*glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
	glClear(GL_COLOR_BUFFER_BIT);*/

	
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	//glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);

	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData()); // Rendering


	// Update and Render additional Platform Windows
	//if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	//{
	//		//HDC backup_current_context = GetDC(_window.Get_hwnd());
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
