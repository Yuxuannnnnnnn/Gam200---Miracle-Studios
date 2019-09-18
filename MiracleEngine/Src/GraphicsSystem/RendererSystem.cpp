#include "RendererSystem.h"

RendererSystem::RendererSystem(int windowWidth, int windowHeight)
	: _proj{ glm::ortho(-(float)windowWidth / 2, (float)windowWidth / 2,
		-(float)windowHeight / 2, (float)windowHeight / 2) }
{

}
void RendererSystem::Update()
{
	for (size_t i = 0; i < objList.size(); i++)
	{
		//_meshmanager._quadmesh.Select();

		VertexBuffer vbo(_meshmanager.GetQuadMesh()._positions, _meshmanager.GetQuadMesh().GetVBOSize()); // bind vbo, bind, ebo must bind every single loop
		ElementBuffer ebo(_meshmanager.GetQuadMesh()._indices, _meshmanager.GetQuadMesh().GetIndicesCount());

		glEnableVertexAttribArray(0);

		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

		_shader.Select();

		glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(objList[i]._pos._x
			, objList[i]._pos._y, 0));
		glm::mat4 rotate = glm::rotate(glm::mat4(1.0f), objList[i]._angle, glm::vec3(0, 0, 1));
		glm::mat4 model = translate * glm::scale(glm::mat4(1.0f),
			glm::vec3(objList[i]._scale._x, objList[i]._scale._y, 1.0f));

		glm::mat4 mvp = _proj * model;

		_shader.SetUniform4f("u_Color", 1.0f, 0.0f, 0.0f, 1.0f);
		_shader.SetUniformMat4f("u_MVP", mvp);

		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		// this one encapsulate into another class
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
	}
}
void RendererSystem::DrawPoint(int x, int y, int size)
{
	GLfloat positions[] =
	{
		0.0f, 0.0f
	};
	VertexBuffer vbo(positions, 2 * sizeof(GLfloat)); // bind vbo, bind, ebo must bind every single loop
	glPointSize(size);


	_shader.Select();

	glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, 0));


	glm::mat4 mvp = _proj * model;

	int location = glGetUniformLocation(_shader._id, "u_Color");
	glUniform4f(location, 1.0f, 0.0f, 0.0f, 1.0f);

	location = glGetUniformLocation(_shader._id, "u_MVP");
	glUniformMatrix4fv(location, 1, GL_FALSE, &mvp[0][0]);

	// this one encapsulate into another class
	glDrawArrays(GL_POINTS, 0, 1);
}

void RendererSystem::DrawWireFrameQuad(int xpos, int ypos, int xsize, int ysize)
{
	VertexBuffer vbo(_meshmanager.GetQuadMesh()._positions, _meshmanager.GetQuadMesh().GetVBOSize()); // bind vbo, bind, ebo must bind every single loop
	ElementBuffer ebo(_meshmanager.GetQuadMesh()._indices, _meshmanager.GetQuadMesh().GetIndicesCount());

	glEnableVertexAttribArray(0);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);




	_shader.Select();

	glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(xpos, ypos, 0));
	glm::mat4 rotate = glm::rotate(glm::mat4(1.0f), objList[0]._angle, glm::vec3(0, 0, 1));
	glm::mat4 model = translate * glm::scale(glm::mat4(1.0f), glm::vec3(xsize, ysize, 1.0f));

	glm::mat4 mvp = _proj * model;

	_shader.SetUniform4f("u_Color", 1.0f, 0.0f, 0.0f, 1.0f);
	_shader.SetUniformMat4f("u_MVP", mvp);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	// this one encapsulate into another class
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
void RendererSystem::DrawLine(int x1, int y1, int x2, int y2)
{
	int windowWidth = 800;
	int windowHeight = 600;
																															 // z-layer -100 to 100
	glm::mat4 proj = glm::ortho(-(float)windowWidth / 2, (float)windowWidth / 2, -(float)windowHeight / 2, (float)windowHeight / 2, -100.f, 100.f);


	_shader.Select();


	int x = (x1 + x2) / 2;
	int y = (y1 + y2) / 2;

	glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
	glm::mat4 mvp = _proj * model;

	int location = glGetUniformLocation(_shader._id, "u_Color");
	glUniform4f(location, 1.0f, 0.0f, 0.0f, 1.0f);

	location = glGetUniformLocation(_shader._id, "u_MVP");
	glUniformMatrix4fv(location, 1, GL_FALSE, &mvp[0][0]);

	GLfloat lineVertices[] =
	{
		200,0,0,
		-200,0,0
	};

	VertexBuffer vbo(lineVertices, 3 * 2 * sizeof(GLfloat));
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(0,
		3,
		GL_FLOAT, // they a float
		GL_FALSE, // don't need to be normalised
		0,  // how many floats to the next one(be aware btVector3 uses 4 floats)
		0  // where do they start as an index); 
	);
	glEnableVertexAttribArray(0);
	glDrawArrays(GL_LINES, 0, 6);


	//// this one encapsulate into another class
	//glDrawArrays(GL_LINES, 0, 2);
}