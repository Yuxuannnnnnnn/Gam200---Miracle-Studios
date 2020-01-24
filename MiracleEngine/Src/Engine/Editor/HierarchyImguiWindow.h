#pragma once
#include "IBaseImguiWindow.h"
#include "InspectionImguiWindow.h"
#include "GameObject/GameObject.h"
#include <string> //std::string


#ifndef HIERARCHY_IMGUI_WINDOW_H
#define HIERARCHY_IMGUI_WINDOW_H


//Hierarchy window should display all the GameObjects present in the current level when data file is loaded, 
//as well as the ability to remove or add objects
//When removing objects, make sure to remove child object along with parent object
class HierarchyImguiWindow : public IBaseImguiWindow
{
	bool isObjectSelected;
	std::string selectedObj;


public:

	HierarchyImguiWindow(bool open = true,	//Set the settings for the imgui window
		ImGuiWindowFlags flags = ImGuiWindowFlags_::ImGuiWindowFlags_MenuBar);


	void Update() override; //Content for every frame


	void ShowGameObjects(); //Show Every GameObject in the GameObjectList
	//void ShowGameObjectComponents(std::unordered_map < unsigned, IComponent* > ComponentList); //Show every Component of a GameObject
	//
	//
	//void ShowTransformComponent(IComponent* component);
	//void ShowGraphicsComponent(IComponent* component);
	//void ShowRigidBodyComponent(IComponent* component);
	//void ShowColliderComponent(IComponent* component);
	//void ShowLogicComponent(IComponent* component);
	//void ShowAudioCommponent(IComponent* component);
	void SetisObjectSelected(bool set)
	{
		isObjectSelected = set;
	}

	bool GetObjIsSelected()
	{
		return isObjectSelected;
	}

	void SetSelectedObj(GameObject * ObjName)
	{
		IdentityComponent* IdCom = dynamic_cast<IdentityComponent*>(ObjName->GetComponent(ComponentId::CT_Identity));
		selectedObj = std::to_string(IdCom->GetParentId()) + " " + IdCom->GetName();
		isObjectSelected = true;
	}
};

#endif


