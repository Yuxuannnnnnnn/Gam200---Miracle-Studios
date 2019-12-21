#include "PrecompiledHeaders.h"
#include "Renderer.h"

void Renderer::Update(const std::vector<std::vector<RenderObject>>& _renderObjects, const glm::mat4& proj) const
{
	for (const auto& renderObjList : _renderObjects)
	{
		renderObjList[0]._pShader->Select();
		renderObjList[0]._pTexture->Select();
		renderObjList[0]._pMesh->Select();

		for (const auto& renderobj : renderObjList)
		{
			glm::mat4 mvp = proj * renderobj.transform;
			renderObjList[0]._pShader->SetUniformMat4f("u_MVP", mvp);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
		}
	}
	
}
