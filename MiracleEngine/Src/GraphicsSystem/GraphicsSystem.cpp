#include "GraphicsSystem.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "GraphicsSystem/VertexBuffer.h"


#include "GraphicsSystem/RendererSystem.h"


void GraphicsSystem::Init()
{
	glewInit();

}
void GraphicsSystem::Update()
{
	//glm::vec2 positions[3] = {
	//{ -0.5f, -0.5f },
	//{ 0.0f, 0.5f   },
	//{ 0.5f, -0.5f  }
	//};

	//VertexBuffer vb((const void*)positions, sizeof(glm::vec2) * 3);

	////each function call: create layout for each vertex attribute
	////1. index of attribute of vertex
	////2. number of floats for the attribute
	////3. type of data
	////4. To normalise or not
	////5. Size(bytes) of Stride from vertex to vertex
	////6. offset of number of bytes in a vertex to get to the attribute
	//glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (const void*)0);

	////enable the index of the vertex attribute
	//glEnableVertexAttribArray(0);


	//Clear the color buffer / Clear the screen
	glClear(GL_COLOR_BUFFER_BIT);

	//glBegin(GL_TRIANGLES);
	//glVertex2f(-0.5f, -0.5f);
	//glVertex2f(-0.0f, 0.5f);
	//glVertex2f(0.5f, -0.5f);
	//glEnd();

	glClearColor(.0f, .0f, .0f, 1.0f);


	/*glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_TRIANGLES);
	glVertex2f(-0.5f, -0.5f);
	glVertex2f(-0.0f, 0.5f);
	glVertex2f(0.5f, -0.5f);
	glEnd();*/

	RendererSystem rs;

	rs.DrawPoint(10, -100, 5);
	rs.DrawWireFrameQuad(0, 0, 30, 50);
	rs.DrawLine(-100, -100, 100, 100);
	// gl_lines
	// 2 vbo and ebo
	// 1 for square and 1 for lines
}
void GraphicsSystem::Exit()
{

}