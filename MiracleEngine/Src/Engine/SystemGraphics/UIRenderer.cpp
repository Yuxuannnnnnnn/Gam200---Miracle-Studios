#include "UIRenderer.h"
#include "PrecompiledHeaders.h"

UIRenderer::UIRenderer()
{
	// temp
	std::string temp = "DefaultShader";

	_uiShader = MyResourceSystem.GetShaderResource(temp);

	if (!_uiShader && MyResourceSystem.AddNewShaderResource({ temp,{ "Resources/Shader/basic.vert", "Resources/Shader/basic.frag" } }))
	{
		_uiShader = MyResourceSystem.GetShaderResource(temp);
	}
}

void UIRenderer::Update(std::unordered_map<size_t, IComponent*> uiMap, const glm::mat4& proj)
{
	for (const auto& uiCompPair : uiMap)
	{
		if (uiCompPair.second->GetParentPtr()->GetDestory() || !uiCompPair.second->GetEnable())
			continue;

		UIComponent* uiComp = (UIComponent*)uiCompPair.second;

		size_t objID = uiCompPair.first;	//Get GameObjectID
		TransformComponent* transformComp = (TransformComponent*)GetComponentMap(Transform)[objID];

		glm::mat4 modelTransform = glm::make_mat4(Mtx44::CreateTranspose(transformComp->GetModel()).m);

		glm::mat4 mvp = proj * modelTransform;

		auto pTexture = MyResourceManager.GetTexture2DResource(uiComp->GetFileName());

		if (pTexture && !uiComp->GetFileName().empty())
		{
			pTexture->Select();
			_uiMesh.Select();
			_uiShader->Select();

			_uiShader->SetUniformMat4f("u_MVP", mvp);

			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
		}
	}
}
