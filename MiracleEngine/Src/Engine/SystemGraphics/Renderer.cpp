#include "PrecompiledHeaders.h"
#include "Renderer.h"

void Renderer::Update(const std::vector<std::vector<RenderObject>>& _renderObjects, const glm::mat4& proj) const
{
	// render object from back to front, 0 at back, 10 front

	/*for (size_t i = 0; i < _renderObjects.size(); i++)
	{
		for (const auto& renderobj : _renderObjects[i])
		{
			renderobj._pShader->Select();
			renderobj._pTexture->Select();
			renderobj._pMesh->Select();

			glm::mat4 mvp = proj * renderobj.transform;
			renderobj._pShader->SetUniformMat4f("u_MVP", mvp);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
		}
	}*/


}
