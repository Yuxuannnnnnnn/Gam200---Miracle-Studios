#include "GraphicsSystem.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "GraphicsSystem/VertexBuffer.h"
#include "PrecompiledHeaders.h"
#include "../Imgui/imgui.h"
#include "Engine/EngineSystems.h"
#include "../LogicSystem/AiSystem.h"
#include "FrameBuffer.h"

void GraphicsSystem::CalculateProjectionMatrix(int windowWidth, int windowHeight)
{
	_proj = glm::ortho(-(float)windowWidth / 2, (float)windowWidth / 2,
		-(float)windowHeight / 2, (float)windowHeight / 2, -15.0f, 15.0f);

	DebugRenderCalculateProjMatrix(windowWidth, windowHeight);
}

void  GraphicsSystem::GetZmoInfo(size_t objectUId, const float*& cameraView, float*& cameraProjection, float*& transformMatrix)
{
	TransformComponent* transform = MyTransformManager.GetTransform(objectUId);

	glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(transform->GetPos()._x
		, transform->GetPos()._y, 0));
	glm::mat4 rotate = glm::rotate(glm::mat4(1.0f), transform->GetRotate(), glm::vec3(0, 0, 1));
	glm::mat4 model = translate * rotate * glm::scale(glm::mat4(1.0f),
		glm::vec3(transform->GetScale()._x, transform->GetScale()._y, 1.0f));

	cameraView = (const float*)glm::value_ptr(_camera.GetCamMatrix());
	cameraProjection = (float*)glm::value_ptr(_proj);
	transformMatrix = (float*)glm::value_ptr(model);
}

GraphicsSystem::GraphicsSystem(int windowWidth, int windowHeight) : _proj{ glm::ortho(-(float)windowWidth / 2, (float)windowWidth / 2,
		-(float)windowHeight / 2, (float)windowHeight / 2, -15.0f, 15.0f) }
{
	std::string temp = "DefaultShader";

	_shader = ResourceManager::GetInstance().GetShaderResource(temp);

	if (!_shader && ResourceManager::GetInstance().AddNewShaderResource({ temp,{ "Resources/Shader/basic.vert", "Resources/Shader/basic.frag" } }))
	{
		_shader = ResourceManager::GetInstance().GetShaderResource(temp);
	}

	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);


	temp = "arial";

	_fontRenderer = ResourceManager::GetInstance().GetFontResource(temp);

	if (!_fontRenderer && ResourceManager::GetInstance().AddNewFontResource({ temp,"Resources/Fonts/arial.ttf" }))
	{
		_fontRenderer = ResourceManager::GetInstance().GetFontResource(temp);
	}
}

Camera& GraphicsSystem::GetCamera()
{
	return _camera;
}


const TextureManager& GraphicsSystem::GetTextureManager() const
{
	return _textureManager;
}

void GraphicsSystem::Update(double dt)
{
	
	//DrawDebugLine(0.0f, 0.0f, 100.0f, 200.0f);
	
	//DrawDebugLine(0.0f, 0.0f, .0f, 100.0f);
	

	UnitTest();
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0);
	ClearScreen();

	// batch render
	//DrawDebugLine(-100.0f, 0.0f, -100.0f, 100.0f);

	// non - batch
	//DebugRenderer::GetInstance().DrawLine(-150.0f, 0.0f, -150.0f, 100.0f);

	// flush the batch vertices
	DebugRendererLineDraw();

	_animationSystem.Update(_animationList, dt);

	_camera.Update();
	//Check for Graphic component first then get Transform COmponent
	for (auto& graphicComponentpair : _spriteList)
	{
		GraphicComponent* graphicComponent = graphicComponentpair.second;

		if (!graphicComponent->GetEnable())
			continue;
		/*
				if (graphicComponent->GetRenderLayer() == 10)
					continue;*/
		size_t objID = graphicComponentpair.first;	//Get GameObjectID
		TransformComponent* transformComponent = MyTransformManager.GetTransform(objID); //Get transform from GameObjectID

		glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_SRC_ALPHA, GL_DST_ALPHA);

		// checking if have animation comp
			//if(graphicComponent->GetSibilingComponent((unsigned int)ComponentId::ANIMATION_COMPONENT))


			// texture with animation
		if (graphicComponent->GetSibilingComponent(ComponentId::ANIMATION_COMPONENT))
		{
			AnimationComponent* anim = (AnimationComponent*)graphicComponent->GetSibilingComponent(ComponentId::ANIMATION_COMPONENT);

			anim->testanim->Select();
			//_testAnimation.Select();
			_textureManager._textureMap[anim->GetFilePath()]->Select();

		}
		else
			// texture without animation
		{
			if (EngineSystems::GetInstance()._sceneManager->GetCurrentScene().compare("MainMenu") == 0)
			{
				_uimesh.Select();
				//_quadmesh.Select();
			}
			else
			_quadmesh.Select();
			

			Texture2D* temp = _textureManager._textureMap[graphicComponent->GetFileName()];
			temp->Select();
		}

		_shader->Select();


		// calculate model matrix = TRS
		glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(transformComponent->GetPos()._x
			, transformComponent->GetPos()._y, graphicComponent->GetRenderLayer()));
		glm::mat4 rotate = glm::rotate(glm::mat4(1.0f), transformComponent->GetRotate(), glm::vec3(0, 0, 1));
		glm::mat4 model = translate * rotate * glm::scale(glm::mat4(1.0f),
			glm::vec3(transformComponent->GetScale()._x, transformComponent->GetScale()._y, 1.0f));

		glm::mat4 mvp = _proj * _camera.GetCamMatrix() * model;

		//_shader.SetUniform4f("u_Color", 1.0f, 0.0f, 0.0f, 1.0f);

		_shader->SetUniformMat4f("u_MVP", mvp);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
	}

	if (EngineSystems::GetInstance()._sceneManager->GetCurrentScene().compare("MainMenu") == 0)
	{
		_fontRenderer->Draw();
	}

	for (auto& e : _fontList)
	{
		FontComponent* fontcomptr = e.second;
		//TransformComponent* transptr = (TransformComponent*)fontcomptr->GetSibilingComponent((unsigned int)ComponentId::TRANSFORM_COMPONENT);
		//if (transptr)
			//_fontRenderer.DrawFont(fontcomptr->GetFontString(), transptr->GetPos()._x, transptr->GetPos()._y);
	}

	//for (auto& fontComponentpair : EngineSystems::GetInstance()._gameObjectFactory->getFontComponent())
	//{

	//	//_fontRenderer.Draw();

	//	//size_t objID = fontComponentpair.first;	//Get GameObjectID
	//	//TransformComponent* transformComponent = _transformList[objID]; //Get transform from GameObjectID

	//	//_fontRenderer.DrawFont(fontComponentpair.second->GetFontString(), transformComponent->GetPos()._x,
	//	//	transformComponent->GetPos()._y, glm::vec3(0.2f, 0.8f, 0.2f));
	//}

	// loop through every element in graphic component
		// get texture ID and shader ID
		// get its transform component 

	
}


void GraphicsSystem::Exit()
{
}

void GraphicsSystem::ClearScreen() const
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(.0f, .0f, .0f, 1.0f);
}


void GraphicsSystem::UnitTest()
{
	if (EngineSystems::GetInstance()._inputSystem->KeyHold(KeyCode::KEYB_Z))
	{
		_camera.ZoomIn(0.1f);
	}
	if (EngineSystems::GetInstance()._inputSystem->KeyHold(KeyCode::KEYB_X))
	{
		_camera.ZoomOut(0.1f);
	}

	if (EngineSystems::GetInstance()._inputSystem->KeyHold(KeyCode::KEYB_C))
	{
		_camera.MoveCameraX(1.0f);
	}
	if (EngineSystems::GetInstance()._inputSystem->KeyHold(KeyCode::KEYB_V))
	{
		_camera.MoveCameraX(-1.0f);
	}
	if (EngineSystems::GetInstance()._inputSystem->KeyHold(KeyCode::KEYB_B))
	{
		_camera.MoveCameraY(1.0f);
	}
	if (EngineSystems::GetInstance()._inputSystem->KeyHold(KeyCode::KEYB_N))
	{
		_camera.MoveCameraY(-1.0f);
	}
	if (EngineSystems::GetInstance()._inputSystem->KeyHold(KeyCode::KEYB_P))
	{
		_numAnim = 0;
	}
	if (EngineSystems::GetInstance()._inputSystem->KeyHold(KeyCode::KEYB_O))
	{
		_numAnim = 1;
	}
	if (EngineSystems::GetInstance()._inputSystem->KeyHold(KeyCode::KEYB_I))
	{
		_numAnim = 2;
	}
	if (EngineSystems::GetInstance()._inputSystem->KeyHold(KeyCode::KEYB_0))
	{
		_testAnim = 0;
	}
	if (EngineSystems::GetInstance()._inputSystem->KeyHold(KeyCode::KEYB_9))
	{
		_testAnim = 1;
	}

	if (EngineSystems::GetInstance()._inputSystem->KeyHold(KeyCode::KEYB_8))
	{
		_showfont = 1;
	}

	if (EngineSystems::GetInstance()._inputSystem->KeyHold(KeyCode::KEYB_7))
	{
		_showfont = 0;
	}
}

void GraphicsSystem::AddFontObject(size_t uId, void* component)
{
	_fontList.insert({ uId, (FontComponent*)component });
}

void GraphicsSystem::RemoveFontObject(size_t uId)
{
	_fontList.erase(uId);
}

void GraphicsSystem::AddSpriteObject(size_t uId, void* component)
{
	_spriteList.insert({ uId, (GraphicComponent*)component });
}

void GraphicsSystem::RemoveSpriteObject(size_t uId)
{
	_spriteList.erase(uId);
}

void GraphicsSystem::AddAnimationObject(size_t uId, void* component)
{
	_animationList.insert({ uId, (AnimationComponent*)component });
}

void GraphicsSystem::RemoveAnimationObject(size_t uId)
{
	_animationList.erase(uId);
}
