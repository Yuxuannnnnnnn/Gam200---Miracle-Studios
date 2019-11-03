#pragma once
#include "IBaseImguiWindow.h"
#include "InspectionImguiWindow.h"
#include "GameObjectFactory/GameObject.h"
#include <string> //std::string


#ifndef HIERARCHY_IMGUI_WINDOW_H
#define HIERARCHY_IMGUI_WINDOW_H


//Hierarchy window should display all the GameObjects present in the current level when data file is loaded, 
//as well as the ability to remove or add objects
//When removing objects, make sure to remove child object along with parent object
class HierarchyImguiWindow : public IBaseImguiWindow
{
public:

	HierarchyImguiWindow(bool open = true,	//Set the settings for the imgui window
		ImGuiWindowFlags flags = ImGuiWindowFlags_::ImGuiWindowFlags_MenuBar);


	void Update() override; //Content for every frame


	void ShowGameObjects(); //Show Every GameObject in the GameObjectList
	//void ShowGameObjectComponents(std::unordered_map < unsigned, IComponentSystem* > ComponentList); //Show every Component of a GameObject
	//
	//
	//void ShowTransformComponent(IComponentSystem* component);
	//void ShowGraphicsComponent(IComponentSystem* component);
	//void ShowRigidBodyComponent(IComponentSystem* component);
	//void ShowColliderComponent(IComponentSystem* component);
	//void ShowLogicComponent(IComponentSystem* component);
	//void ShowAudioCommponent(IComponentSystem* component);
};

#endif


