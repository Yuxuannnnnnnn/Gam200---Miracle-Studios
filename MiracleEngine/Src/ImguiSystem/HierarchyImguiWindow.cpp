#include "PrecompiledHeaders.h"
#include "HierarchyImguiWindow.h"

#include "GameObject.h"
#include "Main.h" //Use GameObjectFactory Global pointer
#include <string> //std::string





HierarchyImguiWindow::HierarchyImguiWindow(bool open, ImGuiWindowFlags flags)
	:IBaseImguiWindow("Hierarchy", open, flags)
{
}




void HierarchyImguiWindow::Update()  //Update() function used in ImguiSystem.cpp
{
	ShowGameObjects();				//Show Every GameObject in the GameObjectList
}



void HierarchyImguiWindow::ShowGameObjects()			//Show Every GameObject in the GameObjectList - Used in Update() 
{
	const std::unordered_map<size_t, GameObject*>& objlist = gameObjectFactory->getObjectlist();

	for (auto& gameObjectPair : objlist)
	{
		GameObject* gameObject = gameObjectPair.second; //Get GameObject* from std::pair

		size_t uID = gameObject->Get_uID();				//Get Unique Number of each GameObject
		unsigned ObjectTypeID = gameObject->GameObjectType(); //Get Object Type of each GameObject
		std::string string = ToString((TypeIdGO)ObjectTypeID) + std::string(" ") + std::to_string(uID); // "Object Type + Object unique number" string


		if (ImGui::CollapsingHeader(string.c_str()))	//Start of Each Object Hierarchy
		{
			std::unordered_map < TypeIdComponent, IComponentSystem* > componentList = gameObject->GetComponentList(); //Get ComponenntList from each GameObject
			ShowGameObjectComponents(componentList);	//Show every Component of a GameObject
		}
	}
}



void HierarchyImguiWindow::ShowGameObjectComponents(
	std::unordered_map < TypeIdComponent, IComponentSystem* > componentList)	//Show every Component of a GameObject - Used in ShowGameObjects()
{
	for (auto& iComponentPair : componentList)
	{
		IComponentSystem* component = iComponentPair.second;	//Get component* from std::pair
		TypeIdComponent componentType = iComponentPair.first;	//Get ComponentType from std::pair


		if (ImGui::TreeNode(component->ComponentName().c_str()))
		{

			switch (componentType)	//Calls the Suitable Show Component function that the Object has
			{
			case TypeIdComponent::TRANSFORMCOMPONENT:	ShowTransformComponent(component); break;
			case TypeIdComponent::GRAPHICSCOMPONENT:	ShowGraphicsComponent(component);  break;
			case TypeIdComponent::RIGIDBODYCOMPONENT:	ShowRigidBodyComponent(component); break;
			case TypeIdComponent::COLLIDERCOMPONENT:	ShowColliderComponent(component);  break;
			case TypeIdComponent::LOGICCOMPONENT:		ShowLogicComponent(component);	   break;
			case TypeIdComponent::AUDIOCOMPONENT:		ShowAudioCommponent(component);	   break;
			}

			ImGui::Text("Text");

			ImGui::TreePop();
		}
	}
}


void HierarchyImguiWindow::ShowTransformComponent(IComponentSystem* component)
{


}


void HierarchyImguiWindow::ShowGraphicsComponent(IComponentSystem* component)
{
}


void HierarchyImguiWindow::ShowRigidBodyComponent(IComponentSystem* component)
{
}


void HierarchyImguiWindow::ShowColliderComponent(IComponentSystem* component)
{
}


void HierarchyImguiWindow::ShowLogicComponent(IComponentSystem* component)
{
}


void HierarchyImguiWindow::ShowAudioCommponent(IComponentSystem* component)
{
}




