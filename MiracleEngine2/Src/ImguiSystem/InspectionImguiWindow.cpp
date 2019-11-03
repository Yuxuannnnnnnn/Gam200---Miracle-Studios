#include "PrecompiledHeaders.h"
#include "InspectionImguiWindow.h"


GameObject* InspectionImguiWindow::_inspectObj = nullptr;



InspectionImguiWindow::InspectionImguiWindow(bool open, ImGuiWindowFlags flags)
	:IBaseImguiWindow("Inspection", open, flags)
{
}
