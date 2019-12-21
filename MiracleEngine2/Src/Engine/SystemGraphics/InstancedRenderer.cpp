#include "PrecompiledHeaders.h"
#include "InstancedRenderer.h"

InstancedRenderer::InstancedRenderer(int windowWidth, int windowHeight)
	: _proj{ glm::ortho(-(float)windowWidth / 2, (float)windowWidth / 2,
		-(float)windowHeight / 2, (float)windowHeight / 2) }
{
	

	glGenBuffers(1, &_instanceBufferID);
	modelMatrices = new glm::mat4[1500];

	// stress test

	for (size_t j = 0; j < 1500; j++)
	{
		/*modelMatrices[j] = glm::translate(glm::mat4(1.0f), glm::vec3(objStressTestList[j]->_pos._x
			, objStressTestList[j]->_pos._y, 0)) * glm::scale(glm::mat4(1.0f),
				glm::vec3(objStressTestList[j]->_scale._x, objStressTestList[j]->_scale._y, 1.0f));*/
	}

	glBindBuffer(GL_ARRAY_BUFFER, _instanceBufferID);
	glBufferData(GL_ARRAY_BUFFER, 1500 * sizeof(glm::mat4), &modelMatrices[0], GL_DYNAMIC_DRAW);
}

void InstancedRenderer::Update()
{

	_quadmesh.Select();
	//_shader.Select();

	glm::mat4 vp = _proj;
	glBindBuffer(GL_ARRAY_BUFFER, _instanceBufferID);
	size_t numOfObject = 1500;

	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)0);
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4)));
	glEnableVertexAttribArray(5);
	glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(2 * sizeof(glm::vec4)));
	glEnableVertexAttribArray(6);
	glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(3 * sizeof(glm::vec4)));
	glVertexAttribDivisor(3, 1);
	glVertexAttribDivisor(4, 1);
	glVertexAttribDivisor(5, 1);
	glVertexAttribDivisor(6, 1);

	//_shader.SetUniform4f("u_Color", 1.0f, 0.0f, 0.0f, 1.0f);
	//_shader.SetUniformMat4f("u_VP", vp);
	//_shader.SetUniform1i("u_Texture", 0);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	// this one encapsulate into another class
	//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
	glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr, (GLsizei)numOfObject);

}