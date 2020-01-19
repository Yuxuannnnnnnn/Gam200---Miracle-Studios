#pragma once

#ifndef GRAPHICSYSTEM_H
#define GRAPHICSYSTEM_H

#include "UIRenderer.h"                                  // ui renderer for ui, font etc in screen space
#include "DebugRenderer.h"                               // render debug lines
#include "../SystemCamera/CameraSystem.h"                             // class contain one (or more) cameras


#include "GameObject/Components/Graphic/TransformComponent.h"
#include "GameObject/Components/Graphic/GraphicComponent.h"
#include "GameObject/Components/Graphic/AnimationComponent.h"
#include "GameObject/Components/Graphic/FontComponent.h" 

// glm
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/matrix_transform.hpp"

// renderobjects
#include "RenderObject.h"
#include "QuadMesh.h"

#include <vector>

class GraphicsSystem
{

public:
	// GraphicsSystem(int& windowWidth, int& windowHeight); possible solution to resize : take the reference of window height and width

	void Update(double dt);                              // Update function called every loop
	GraphicsSystem();   // constructor
	~GraphicsSystem();                                   // destructor

	void ResizeGraphics(float width, float height);

private:
	void BeginScene();
	void EndScene();

	void ClearSreen() const;
	void UpdateRenderObjectList();                       // called begin of loop, fill up the render objects list

	//DebugRenderer _debugRenderer;                      // render debug lines
	UIRenderer _uiRenderer;                              // ui renderer for ui, font etc in screen space

	glm::mat4 _proj;                                     // projection matrix depth ( z-axis ) range from -30 to 30
	glm::mat4 _view;                                   // camera view matrix

	CameraSystem _cameraSystem;                        // class manage all the camera
	 

	std::vector<RenderObject> _renderObjects;

	QuadMesh _quadMesh;
	QuadMesh _q2{ 0.0f, 0.0f, 0.5f, 0.5f };
	Shader* _shader;

};

//#define ResizeGraphics EngineSystems::GetInstance()._graphicsSystem->CalculateProjectionMatrix

#endif

