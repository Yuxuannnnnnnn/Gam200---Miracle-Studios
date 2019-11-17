#include "PrecompiledHeaders.h"
#include "HierarchyImguiWindow.h"

#include "GameObjectFactory/GameObject.h"
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

	size_t objListSize = objlist.size(); //number of total gameObjects in the list
	std::string totalGameObjects("Total Number of GameObjects in this level is: ");
	totalGameObjects += std::to_string(objListSize);  //"Total Number of GameObjects in this level is: objListSize" string
	
	ImGui::Text(totalGameObjects.c_str());	//Shows Total Number of GameObjects in this level on Imgui Window


	for (auto& gameObjectPair : objlist)
	{
		GameObject* gameObject = gameObjectPair.second; //Get GameObject* from std::pair

		size_t uID = gameObject->Get_uID();				//Get Unique Number of each GameObject
		IdentityComponent* Icom = dynamic_cast<IdentityComponent*>(gameObject->GetComponent(TypeIdComponent::IDENTITYCOMPONENT));
		unsigned ObjectTypeID = Icom->GameObjectType(); //Get Object Type of each GameObject
		std::string string = ToString((TypeIdGO)ObjectTypeID) + std::string(" ") + std::to_string(uID); // "Object Type + Object unique number" string


		if (ImGui::CollapsingHeader(string.c_str()))	//Start of Each Object Hierarchy
		{
			//std::unordered_map < unsigned, IComponentSystem* > componentList = gameObject->GetComponentList(); //Get ComponenntList from each GameObject
			//ShowGameObjectComponents(componentList);	//Show every Component of a GameObject
		}
	}
}



void HierarchyImguiWindow::ShowGameObjectComponents(
	std::unordered_map < unsigned, IComponentSystem* > componentList)	//Show every Component of a GameObject - Used in ShowGameObjects()
{
	for (auto& iComponentPair : componentList)
	{
		IComponentSystem* component = iComponentPair.second;	//Get component* from std::pair
		unsigned componentType = iComponentPair.first;	//Get ComponentType from std::pair

	}
}





