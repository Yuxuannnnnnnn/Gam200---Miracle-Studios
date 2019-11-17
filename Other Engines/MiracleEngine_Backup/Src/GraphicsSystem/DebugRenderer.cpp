#include "DebugRenderer.h"

DebugRenderer::DebugRenderer(int windowWidth, int windowHeight)
	: _proj{ glm::ortho(-(float)windowWidth / 2, (float)windowWidth / 2,
		-(float)windowHeight / 2, (float)windowHeight / 2) }
{
	_vbo = new VertexBuffer(&verts, 3 * 2 * sizeof(GLfloat));
	_vao = new VertexArray();
	BufferLayout layout;
	layout.Push<float>(3);
	_vao->AddBuffer(*_vbo, layout);
}

void DebugRenderer::Update()
{

}
void DebugRenderer::DrawLine(float x1, float y1, float x2, float y2)
{
	_shader.Select();
	_vao->Select();

	glm::mat4 trans = glm::translate(glm::mat4(1.0f), glm::vec3(x1, y1, 0));
	glm::mat4 model = trans * glm::scale(glm::mat4(1.0f), glm::vec3(x2-x1, y2-y1, 0));
	glm::mat4 mvp = _proj * model;

	int location = glGetUniformLocation(_shader._id, "u_Color");
	glUniform4f(location, 1.0f, 0.0f, 0.0f, 1.0f);

	location = glGetUniformLocation(_shader._id, "u_MVP");
	glUniformMatrix4fv(location, 1, GL_FALSE, &mvp[0][0]);

	glEnableVertexAttribArray(0);
	glDrawArrays(GL_LINES, 0, 2);
}