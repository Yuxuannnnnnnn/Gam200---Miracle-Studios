#include "GraphicsSystem.h"
#include "PrecompiledHeaders.h"

void GraphicsSystem::Update(double dt)
{
	BeginScene();

	//_renderer.Update(_renderObjects, _proj * _cameraManager.GetMainCamMatrix());
	//for (size_t i = 0; i < _renderObjects.size(); i++)
	//{
	for (const auto& renderobj : _renderObjects)
	{
		renderobj._pShader->Select();
		renderobj._pTexture->Select();
		renderobj._pMesh->Select();

		float u0 = renderobj._uv.u0;
		float v0 = renderobj._uv.v0;
		float u1 = renderobj._uv.u1;
		float v1 = renderobj._uv.v1;
		GLfloat _positions[] =
		{
			-0.5f, -0.5f, 0.0f, u0, v0, // 0     // bottom left
			 0.5f, -0.5f, 0.0f, u1, v0,// 1     // bottom right
			 0.5f,  0.5f, 0.0f, u1, v1,// 2     // top right
			-0.5f,  0.5f, 0.0f, u0, v1 // 3     // top left
		};

		renderobj._pMesh->GetBuffer()->FillDynamicBuffer(_positions, 4 * 5 * sizeof(GLfloat));

		glm::mat4 mvp = _proj * _cameraManager.GetMainCamMatrix() * renderobj._transform;
		renderobj._pShader->SetUniformMat4f("u_MVP", mvp);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
	}
	//}

	EndScene();
}

void GraphicsSystem::BeginScene()
{
	UpdateRenderObjectList();
	ClearSreen();
}

void GraphicsSystem::EndScene()
{
	_renderObjects.clear();
	/*for (auto& element : _renderObjects)
	{
		element.clear();
	}*/
}

GraphicsSystem::GraphicsSystem(int windowWidth, int windowHeight)
	: _proj{ glm::ortho(-(float)windowWidth / 2, (float)windowWidth / 2,
			-(float)windowHeight / 2, (float)windowHeight / 2, -30.0f, 30.0f) }
{
	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);


	// temp set view to identity
	//_view = glm::mat4(1.0f);

	/*for (size_t i = 0; i <= 10; i++)
	{
		_renderObjects.push_back(std::vector<RenderObject>{});
	}*/

	// temp
	std::string temp = "DefaultShader";

	_shader = MyResourceSystem.GetShaderResource(temp);

	if (!_shader && MyResourceSystem.AddNewShaderResource({ temp,{ "Resources/Shader/basic.vert", "Resources/Shader/basic.frag" } }))
	{
		_shader = MyResourceSystem.GetShaderResource(temp);
	}
}

GraphicsSystem::~GraphicsSystem()
{
}



void GraphicsSystem::ClearSreen() const
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void GraphicsSystem::UpdateViewMatrix()
{
	_cameraManager.Update();
}

void GraphicsSystem::UpdateRenderObjectList()
{

	// update 
	std::vector<RenderObject> renderObj;

	BBox viewBox = BBox::CreateBBoxFromData(Vec3::Vec3Zero,
		Vec3{ MyWindowsSystem.getWindow().GetWindowWidth() * 0.75f ,MyWindowsSystem.getWindow().GetWindowHeight() * 0.75f },
		0.f);

	for (auto& graphicCompPair : MyComponentManger._graphicComponents)
	{
		if (graphicCompPair.second->GetParentId() < 1000 || graphicCompPair.second->GetParentPtr()->GetDestory())
			continue;

		GraphicComponent* graphicComp = graphicCompPair.second;
		if (!graphicComp->GetEnable())
			continue;
		
		RenderObject renderobject;

		// check for if obj have animation

		if (graphicComp->GetSibilingComponent(ComponentId::CT_Animation))
		{
			AnimationComponent* anim = (AnimationComponent*)graphicComp->GetSibilingComponent(ComponentId::CT_Animation);

			// get animation from resource manager
			Animation* currAnim = MyResourceManager.GetAnimationResource(anim->GetCurrAnim());
			


			renderobject._uv.u0 = currAnim->GetCurrFrame(anim->_currFrame)->_u0;
			renderobject._uv.v0 = currAnim->GetCurrFrame(anim->_currFrame)->_v0;
			renderobject._uv.u1 = currAnim->GetCurrFrame(anim->_currFrame)->_u1;
			renderobject._uv.v1 = currAnim->GetCurrFrame(anim->_currFrame)->_v1;

			//anim->testanim->Select();
			////_testAnimation.Select();
			//_textureManager._textureMap[anim->GetFilePath()]->Select();

		}


		size_t objID = graphicCompPair.first;	//Get GameObjectID
		TransformComponent* transformComp = MyComponentManger._transformComponents[objID];

		if (!Collision::DefaultColliderDataCheck(viewBox,
			BBox::CreateBBoxFromData(transformComp->GetPos(), transformComp->GetScale(), transformComp->GetRotate())))
			continue;


		glm::mat4 modelTransform = glm::make_mat4(Mtx44::CreateTranspose(transformComp->GetModel()).m);





		renderobject._pMesh = &_quadMesh;
		renderobject._pShader = _shader;
		renderobject._pTexture = MyResourceManager.GetTexture2DResource(graphicComp->GetFileName());
		renderobject._transform = modelTransform;
		_renderObjects.push_back(renderobject);


	}

}
