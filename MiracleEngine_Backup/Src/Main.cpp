// MiracleEngine.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "glew.h"
#include <iostream>
#include "Engine/Engine.h"
#include "MathLib/SYMath.h"

#include "Inputsystem/InputSystem.h"
#include "../Imgui/imgui.h"
#include "../Imgui/imgui_impl_win32.h"
#include "../Imgui/imgui_impl_opengl3.h"
#include "../Imgui/imgui_internal.h"


InputSystem* inputsystem;


void showWindowBegin()
{

	IM_ASSERT(ImGui::GetCurrentContext() != NULL && "Missing dear imgui context. Refer to examples app!"); // Exceptionally add an extra assert here for people confused with initial dear imgui setup

	// Demonstrate the various window flags. Typically you would just use the default!
	static bool no_titlebar = false;
	static bool no_scrollbar = false;
	static bool no_menu = false;
	static bool no_move = false;
	static bool no_resize = false;
	static bool no_collapse = false;
	static bool no_close = false;
	static bool no_nav = false;
	static bool no_background = false;
	static bool no_bring_to_front = false;

	bool* p_open = NULL;

	ImGuiWindowFlags window_flags = 0;
	if (no_titlebar)        window_flags |= ImGuiWindowFlags_NoTitleBar;
	if (no_scrollbar)       window_flags |= ImGuiWindowFlags_NoScrollbar;
	if (!no_menu)           window_flags |= ImGuiWindowFlags_MenuBar;
	if (no_move)            window_flags |= ImGuiWindowFlags_NoMove;
	if (no_resize)          window_flags |= ImGuiWindowFlags_NoResize;
	if (no_collapse)        window_flags |= ImGuiWindowFlags_NoCollapse;
	if (no_nav)             window_flags |= ImGuiWindowFlags_NoNav;
	if (no_background)      window_flags |= ImGuiWindowFlags_NoBackground;
	if (no_bring_to_front)  window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus;
	if (no_close)           p_open = NULL; // Don't pass our bool* to Begin

	ImGui::Begin("Debug Console", p_open, window_flags);
	ImGui::End();
	// Main body of the Demo window starts here.
	if (!ImGui::Begin("Debug Console1", p_open, window_flags));
	//{
	//	// Early out if the window is collapsed, as an optimization.
	//	ImGui::End();
	//	return;
	//}

}


void showWindowEnd()
{
	// End of ShowWindow()
	ImGui::End();
}



int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	//Obsolete parameters
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);


	CreateConsole();

	//Creating the window object
	WindowsSystem window(hInstance, nCmdShow);
	window.Initialise();


	Engine* coreEngine = new Engine;
	coreEngine->Init();
	inputsystem = coreEngine->_inputSystem;

    MSG msg;
	bool loop = true;

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;// Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable; // Enable Docking
	io.ConfigDockingWithShift = true;
	//io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable; //Enable Multi - Viewport / Platform Windows



	//Set Window bg color
	ImVec4 clear_color = ImVec4(1.000F, 1.000F, 1.000F, 1.0F);

	// Setup style
	ImGui::StyleColorsDark();

	// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
	//ImGuiStyle& style = ImGui::GetStyle();
	//if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	//{
	//	style.WindowRounding = 0.0f;
	//	style.Colors[ImGuiCol_WindowBg].w = 1.0f;
	//}


	//Init Win32
	ImGui_ImplWin32_Init(window.Get_hwnd());

	//Init OpenGL Imgui Implementation
	// GL 3.0 + GLSL 130
	const char* glsl_version = "#version 130";
	ImGui_ImplOpenGL3_Init(glsl_version);


	while (loop)
	{
		// Main message loop:
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{

			if (msg.message == WM_QUIT)
			{
				//loop = false;

				// Cleanup
				ImGui_ImplOpenGL3_Shutdown();
				ImGui_ImplWin32_Shutdown();
				ImGui::DestroyContext();
				// engine exit here
				coreEngine->Exit();


				return (int)msg.wParam;
			}

			if (!TranslateAccelerator(msg.hwnd, window.get_hAccelTable(), &msg))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			
		}

		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();
		

		ImGui::ShowDemoWindow();
		//show Main Window
		showWindowBegin();
		// Rendering

		// frame buffer object

		// engine update here

		coreEngine->Update();

		showWindowEnd();

		ImGui::Render();


		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		// Update and Render additional Platform Windows
		//if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		//{
		//	ImGui::UpdatePlatformWindows();
		//	ImGui::RenderPlatformWindowsDefault();
		//}

		// swap double buffer at the end
		::SwapBuffers(window.get_m_windowDC());

		if (inputsystem->KeyDown(KEYB_ESCAPE))
		{
			loop = false;
		}

	}

	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
	// engine exit here
	coreEngine->Exit();

    return (int) msg.wParam;
}









