// MiracleEngine.cpp : Defines the entry point for the application.
//
#include "PrecompiledHeaders.h"
#include "Main.h"
#include "glew.h"

#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_win32.h"
#include "imgui_internal.h"

GraphicsSystem* graphicsSystem;
GameObjectFactory* gameObjectFactory;





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
	gameObjectFactory = coreEngine->_gameObjectFactory;
	graphicsSystem = coreEngine->_graphicsSystem;
	coreEngine->Init();



    MSG msg;
	bool loop = true;


	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();  (void)io;


	//Init Win32
	ImGui_ImplWin32_Init(window.Get_hwnd());
	//Init OpenGL Imgui Implementation
	// GL 3.0 + GLSL 130
	const char* glsl_version = "#version 130";
	ImGui_ImplOpenGL3_Init(glsl_version);

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	ImVec4 clear_color = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);

	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;// Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_DockingEnable; // Enable Docking
	//io.ConfigDockingWithShift = true;
	//io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable; //Enable Multi - Viewport / Platform Windows
	// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
	//ImGuiStyle& style = ImGui::GetStyle();
	//if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	//{
	//	style.WindowRounding = 0.0f;
	//	style.Colors[ImGuiCol_WindowBg].w = 1.0f;
	//}

	// testing gameobject, delete later
	//objList.push_back(GameObject{});
	//objList.push_back(GameObject{ Vec3{100,50}, Vec3{50,50} });
	// engine start here
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


			// Start the Dear ImGui frame
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplWin32_NewFrame();
			ImGui::NewFrame();

			ImGui::ShowDemoWindow();


			// engine update here
			coreEngine->Update();

			// Rendering
			ImGui::Render();
			glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
			glClear(GL_COLOR_BUFFER_BIT);

			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
			//if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
			//{
			//	ImGui::UpdatePlatformWindows();
			//	ImGui::RenderPlatformWindowsDefault();
			//}
			// swap double buffer at the end
			::SwapBuffers(window.get_m_windowDC());
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







