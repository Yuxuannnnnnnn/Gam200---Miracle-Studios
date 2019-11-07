#include "GraphicsSystem.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "GraphicsSystem/VertexBuffer.h"
#include "PrecompiledHeaders.h"
#include "../Imgui/imgui.h"
#include "Engine/EngineSystems.h"

GraphicsSystem::GraphicsSystem(int windowWidth, int windowHeight) : _proj{ glm::ortho(-(float)windowWidth / 2, (float)windowWidth / 2,
		-(float)windowHeight / 2, (float)windowHeight / 2, -15.0f, 15.0f) }
{
	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);

}

Camera& GraphicsSystem::GetCamera()
{
	return _camera;
}


void GraphicsSystem::Update(double dt)
{
	

	_camera.Update(_transformList);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0);
	ClearScreen();
	//Example
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
		TransformComponent* transformComponent = _transformList[objID]; //Get transform from GameObjectID

		glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_SRC_ALPHA, GL_DST_ALPHA);
		/*if (graphicComponent->GetFileName() == "spriteplayer.png")
		{
			if (!_testAnim)
			{
				_quadmesh.Select();
				_textureManager._textureMap["player"]->Select();
			}
			else
			{
				_playerMesh.Select(dt, _numAnim);
				switch (_numAnim)
				{
				case 0:
					_textureManager._textureMap["idle"]->Select();
					break;
				case 1:
					_textureManager._textureMap["run"]->Select();
					break;
				case 2:
					_textureManager._textureMap["jump"]->Select();
					break;
				}
			}

		}
		else if (graphicComponent->GetFileName() == "spriteenemy.png"
			&& graphicComponent->GetTextureState() == 0)
		{
			_quadmesh.Select();
			_textureManager._textureMap["enemy1"]->Select();
		}
		else if (graphicComponent->GetFileName() == "spriteenemy.png"
			&& graphicComponent->GetTextureState() == 1)
		{
			_quadmesh.Select();
			_textureManager._textureMap["enemy2"]->Select();
		}
		else if (graphicComponent->GetFileName() == "spritewall.png")
		{
			_quadmesh.Select();
			_textureManager._textureMap["wall"]->Select();
		}
		else if (graphicComponent->GetFileName() == "spritefloor.png")
		{
			_quadmesh.Select();
			_textureManager._textureMap["floor"]->Select();
		}
		else if (graphicComponent->GetFileName() == "spritebullet.png")
		{
			_quadmesh.Select();
			_textureManager._textureMap["bullet"]->Select();
		}
		else
		{
			_quadmesh.Select();
			_textureManager._textureMap["turret"]->Select();
		}*/
		if (graphicComponent->GetFileName() == "player")
		{
			if (!_testAnim)
			{
				_quadmesh.Select();
				_textureManager._textureMap["player"]->Select();
			}
			else
			{
				_playerMesh.Select(dt, _numAnim);
				switch (_numAnim)
				{
				case 0:
					_textureManager._textureMap["idle"]->Select();
					break;
				case 1:
					_textureManager._textureMap["run"]->Select();
					break;
				case 2:
					_textureManager._textureMap["jump"]->Select();
					break;
				}
			}
		}
		else
		{
			_quadmesh.Select();
			_textureManager._textureMap[graphicComponent->GetFileName()]->Select();
		}
		_shader.Select();

		glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(transformComponent->GetPos()._x
			, transformComponent->GetPos()._y, graphicComponent->GetRenderLayer()));
		glm::mat4 rotate = glm::rotate(glm::mat4(1.0f), transformComponent->GetRotate(), glm::vec3(0, 0, 1));
		glm::mat4 model = translate * rotate * glm::scale(glm::mat4(1.0f),
			glm::vec3(transformComponent->GetScale()._x, transformComponent->GetScale()._y, 1.0f));

		glm::mat4 mvp = _proj * _camera.GetCamMatrix() * model;

		//_shader.SetUniform4f("u_Color", 1.0f, 0.0f, 0.0f, 1.0f);
		_shader.SetUniformMat4f("u_MVP", mvp);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
	}

	for (auto& fontComponentpair : EngineSystems::GetInstance()._gameObjectFactory->getFontComponent())
	{

		//_fontRenderer.Draw();

	//	size_t objID = fontComponentpair.first;	//Get GameObjectID
	//	TransformComponent* transformComponent = _transformList[objID]; //Get transform from GameObjectID

	//	_fontRenderer.DrawFont(fontComponentpair.second->GetFontString(), transformComponent->GetPos()._x,
	//		transformComponent->GetPos()._y, glm::vec3(0.2f, 0.8f, 0.2f));
	}

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
}