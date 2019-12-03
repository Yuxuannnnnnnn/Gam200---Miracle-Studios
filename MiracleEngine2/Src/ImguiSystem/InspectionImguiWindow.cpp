#include "PrecompiledHeaders.h"
#include "InspectionImguiWindow.h"


GameObject* InspectionImguiWindow::_inspectObj = nullptr;



InspectionImguiWindow::InspectionImguiWindow(bool open, ImGuiWindowFlags flags)
	:IBaseImguiWindow("Inspection", open, flags)
{
}

void InspectionImguiWindow::Update()
{
	if (_engineSystems._gameObjectFactory->CheckObjOrignialPointer(_inspectObj))
	{
		std::unordered_map < ComponentId, IComponentSystem* > componentList = (_inspectObj)->GetComponentList();
		for (auto& commponentPair : componentList)
		{
			if (ImGui::CollapsingHeader(commponentPair.second->ComponentName().c_str()))
			{
				commponentPair.second->Inspect();
			}
		}
	}
	else
	{
		_inspectObj = nullptr;
	}
}
void InspectionImguiWindow::InspectGameObject(GameObject* inspectObj)
{
	_inspectObj = inspectObj;
	//size_t uID = _inspectObj->Get_uID();				//Get Unique Number of each GameObject
	//unsigned ObjectTypeID = _inspectObj->GameObjectType(); //Get Object Type of each GameObject
	//std::string string = std::string("Inspection Window of ") + ToString((TypeIdGO)ObjectTypeID) + " " + std::to_string(uID); // "Object Type + Object unique number" string
	//IBaseImguiWindow::SetName(string.c_str());
}
