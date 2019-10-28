#pragma once
#include "IBaseImguiWindow.h"


class HierarchyImguiWindow : public IBaseImguiWindow
{
public:

	HierarchyImguiWindow(bool open = true,	//Set the settings for the imgui window
		ImGuiWindowFlags flags = 0);		


	void Update() override; //Content for every frame


	void ShowGameObjects(); //Show Every GameObject in the GameObjectList
	void ShowGameObjectComponents(std::unordered_map < TypeIdComponent, IComponentSystem* > ComponentList); //Show every Component of a GameObject


	void ShowTransformComponent(IComponentSystem* component);
	void ShowGraphicsComponent(IComponentSystem* component);
	void ShowRigidBodyComponent(IComponentSystem* component);
	void ShowColliderComponent(IComponentSystem* component);
	void ShowLogicComponent(IComponentSystem* component);
	void ShowAudioCommponent(IComponentSystem* component);
};

