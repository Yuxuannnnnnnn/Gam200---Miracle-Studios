#include "RendererSystem.h"


RendererSystem::RendererSystem(int windowWidth, int windowHeight)
	: _proj{ glm::ortho(-(float)windowWidth / 2, (float)windowWidth / 2,
		-(float)windowHeight / 2, (float)windowHeight / 2) }
{
	objList.push_back(new GameObject(Vector3{}, Vector3{ 800,600,1 }, 0, "background"));
	objList.push_back(new GameObject(Vector3{350,20}, Vector3{ 50, 50,1 }, 0, "idle"));
}

void RendererSystem::Update(double dt, int num)
{
	for (size_t i = 0; i < objList.size(); i++)
	{
	
		if (objList[i]->_name != "idle")
		{
			_shader.Select();
			_quadmesh.Select();
			_textureManager._textureMap[objList[i]->_name]->Select();
		}
		else
		{
			_shader.Select();
			
			_playermesh.Select(dt, num);
		}
		

		glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(objList[i]->_pos.X()
			, objList[i]->_pos.Y(), 0));
		glm::mat4 rotate = glm::rotate(glm::mat4(1.0f), objList[i]->_angle, glm::vec3(0, 0, 1));
		glm::mat4 model = translate * rotate* glm::scale(glm::mat4(1.0f),
			glm::vec3(objList[i]->_scale.X(), objList[i]->_scale.Y(), 1.0f));

		glm::mat4 mvp = _proj * model;

		_shader.SetUniform4f("u_Color", 1.0f, 0.0f, 0.0f, 1.0f);
		_shader.SetUniformMat4f("u_MVP", mvp);
		_shader.SetUniform1i("u_Texture", 0);
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
	glPointSize((float)size);


	_shader.Select();

	glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, 0));


	glm::mat4 mvp = _proj * model;

	int location = glGetUniformLocation(_shader._id, "u_Color");
	glUniform4f(location, 1.0f, 0.0f, 0.0f, 1.0f);

	location = glGetUniformLocation(_shader._id, "u_MVP");
	glUniformMatrix4fv(location, 1, GL_FALSE, &mvp[0][0]);

	glEnableVertexAttribArray(0);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

	// this one encapsulate into another class
	glDrawArrays(GL_POINTS, 0, 1);
}

void RendererSystem::DrawWireFrameQuad(int xpos, int ypos, int xsize, int ysize)
{
	_quadmesh.Select();

	glEnableVertexAttribArray(0);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);




	_shader.Select();

	glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(xpos, ypos, 0));
	glm::mat4 rotate = glm::rotate(glm::mat4(1.0f), 0.0f, glm::vec3(0, 0, 1));
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
}