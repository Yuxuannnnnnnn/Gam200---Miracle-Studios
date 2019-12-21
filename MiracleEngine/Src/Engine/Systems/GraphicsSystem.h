#pragma once

#ifndef GRAPHICSYSTEM_H
#define GRAPHICSYSTEM_H

#include "HelperClasses/Graphic/Renderer.h"        // normal renderer
#include "HelperClasses/Graphic/UIRenderer.h"      // ui renderer for ui, font etc in screen space
#include "HelperClasses/Graphic/DebugRenderer.h"   // render debug lines
#include "Managers/CameraManager.h"   // class contain one (or more) cameras

// components
// include UI component

#include "Components/TransformComponent.h"
#include "Components/GraphicComponent.h"
#include "Components/AnimationComponent.h"
#include "Components/FontComponent.h" 

// glm
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

// renderobjects
#include "HelperClasses/Graphic/RenderObject.h"
#include <vector>

// temporary
#include "HelperClasses/Graphic/QuadMesh.h"
#include "HelperClasses/Graphic/TextureManager.h"

class GraphicsSystem
{

public:
	// GraphicsSystem(int& windowWidth, int& windowHeight); possible solution to resize : take the reference of window height and width

	void Update(double dt);                              // Update function called every loop
	GraphicsSystem(int windowWidth, int windowHeight);   // constructor
	~GraphicsSystem();                                   // destructor
private:
	void BeginScene();
	void EndScene();
private:
	void ClearSreen() const;
	void UpdateViewMatrix();                             // called begin of loop, fletch the view matrix of the frame from the camera
	void UpdateRenderObjectList();                       // called begin of loop, fill up the render objects list
	glm::mat4 UpdateTransform(TransformComponent*, GraphicComponent*);
private:
	Renderer _renderer;             // normal renderer
	//DebugRenderer _debugRenderer; // render debug lines
	UIRenderer _uiRenderer;         // ui renderer for ui, font etc in screen space
private:
	glm::mat4 _proj;                // projection matrix depth ( z-axis ) range from -30 to 30
	glm::mat4 _view;                // camera view matrix

	CameraManager _cameraManager;   // class manage all the camera
private:
	std::vector<std::vector<RenderObject>> _renderObjects;

	TextureManager _textureManager;
	QuadMesh _quadMesh;
	QuadMesh _q2{ 0.0f, 0.0f, 0.5f, 0.5f };
	Shader* _shader;
public:
	std::unordered_map < size_t, FontComponent*>       _fontCompList;
	std::unordered_map < size_t, AnimationComponent*>  _animationCompList;
	std::unordered_map < size_t, GraphicComponent*>    _graphicCompList;
	std::unordered_map < size_t, TransformComponent*>  _transformCompList;
};

//#define ResizeGraphics EngineSystems::GetInstance()._graphicsSystem->CalculateProjectionMatrix

#endif

