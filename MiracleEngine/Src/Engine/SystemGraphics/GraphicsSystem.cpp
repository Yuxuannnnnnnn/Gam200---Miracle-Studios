#include "GraphicsSystem.h"
#include "PrecompiledHeaders.h"

void GraphicsSystem::Update(double dt)
{
	BeginScene();

	// Render gameobject in world space

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
			 0.5f, -0.5f, 0.0f, u1, v0, // 1     // bottom right
			 0.5f,  0.5f, 0.0f, u1, v1, // 2     // top right
			-0.5f,  0.5f, 0.0f, u0, v1  // 3     // top left
		};

		renderobj._pMesh->GetBuffer()->FillDynamicBuffer(_positions, 4 * 5 * sizeof(GLfloat));

		glm::mat4 mvp = _proj * _view * renderobj._transform;
		renderobj._pShader->SetUniformMat4f("u_MVP", mvp);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
	}

	// render UI in screen space
	_uiRenderer.Update(GetComponentMap(UI), _proj);

	EndScene();
}

void GraphicsSystem::BeginScene()
{
	_cameraSystem.Update();
	_view = _cameraSystem.GetCamMatrix();
	UpdateRenderObjectList();
	ClearSreen();
}

void GraphicsSystem::EndScene()
{
	_renderObjects.clear();
}

GraphicsSystem::GraphicsSystem()
{
	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);

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

void GraphicsSystem::ResizeGraphics(float width, float height)
{
	_proj = glm::ortho(-width / 2.f, width / 2.f, -height / 2.f, height / 2.f, -30.0f, 30.0f);
	glViewport(0, 0, width, height);
}


void GraphicsSystem::ClearSreen() const
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}


void GraphicsSystem::UpdateRenderObjectList()
{

	// update 

	BBox viewBox = BBox::CreateBBoxFromData(Vec3::Vec3Zero,
		Vec3{ MyWindowsSystem.getWindow().GetWindowWidth() ,MyWindowsSystem.getWindow().GetWindowHeight()},
		0.f);

	for (auto& graphicCompPair : GetComponentMap(Graphic))
	{
		if (graphicCompPair.second->GetParentPtr()->GetDestory() || !graphicCompPair.second->GetEnable())
			continue;

		GraphicComponent* graphicComp = (GraphicComponent*)graphicCompPair.second;

		RenderObject renderobject;

		// check for if obj have animation

		if (graphicComp->GetSibilingComponent(ComponentId::CT_Animation))
		{
			AnimationComponent* anim = (AnimationComponent*)graphicComp->GetSibilingComponent(ComponentId::CT_Animation);

			// get animation from resource manager
			Animation* currAnim = MyResourceManager.GetAnimationResource(anim->GetCurrAnim());
			


			renderobject._uv.u0 = currAnim->GetCurrFrame(anim->GetCurrFrame())->_u0;
			renderobject._uv.v0 = currAnim->GetCurrFrame(anim->GetCurrFrame())->_v0;
			renderobject._uv.u1 = currAnim->GetCurrFrame(anim->GetCurrFrame())->_u1;
			renderobject._uv.v1 = currAnim->GetCurrFrame(anim->GetCurrFrame())->_v1;

			//anim->testanim->Select();
			////_testAnimation.Select();
			//_textureManager._textureMap[anim->GetFilePath()]->Select();

		}


		size_t objID = graphicCompPair.first;	//Get GameObjectID
		TransformComponent* transformComp = (TransformComponent*)GetComponentMap(Transform)[objID];

		if (!Collision::DefaultColliderDataCheck(viewBox,
			BBox::CreateBBoxFromData(transformComp->GetPos(), transformComp->GetScale(), transformComp->GetRotate())))
			continue;


		glm::mat4 modelTransform = glm::make_mat4(Mtx44::CreateTranspose(transformComp->GetModel()).m);


		renderobject._pMesh = &_quadMesh;
		renderobject._pShader = _shader;
		renderobject._pTexture = MyResourceManager.GetTexture2DResource(graphicComp->GetFileName());
		renderobject._transform = modelTransform;
		renderobject._zvalue = transformComp->GetPos().GetZ();
		_renderObjects.push_back(renderobject);


	}

}
