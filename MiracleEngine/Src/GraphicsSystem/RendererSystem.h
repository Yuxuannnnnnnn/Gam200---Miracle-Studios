#pragma once
// renderer System expose 3 static function to user: DrawPoint, DrawLine, DrawWireFrameQuad 

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Elementbuffer.h"
#include "VertexBuffer.h"
#include "GraphicsSystem.h"
#include "Shader.h"

class RendererSystem
{
public:
	void DrawPoint(int x, int y, int size)
	{
		int windowWidth = 800;
		int windowHeight = 600;

		glm::mat4 proj = glm::ortho(-(float)windowWidth / 2, (float)windowWidth / 2, -(float)windowHeight / 2, (float)windowHeight / 2);
		GLfloat positions[] =
		{
			0.0f, 0.0f
		};
		VertexBuffer vbo(positions, 2 * sizeof(GLfloat)); // bind vbo, bind, ebo must bind every single loop
		glPointSize(size);

		std::string vertexShader =
			"#version 330 core\n"
			"uniform mat4 u_MVP;\n"
			"layout(location = 0) in vec4 position;"
			"\n"
			"void main()\n"
			"{\n"
			"gl_Position = u_MVP * position;\n"
			"}\n";

		std::string fragmentShader =
			"#version 330 core\n"
			"layout(location = 0) out vec4 color;"
			"uniform vec4 u_Color;\n"
			"void main()\n"
			"{\n"
			"color = u_Color;\n"
			"}\n";

		GLuint shader = CreateShader(vertexShader, fragmentShader);
		glUseProgram(shader);

		glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, 0));


		glm::mat4 mvp = proj * model;

		int location = glGetUniformLocation(shader, "u_Color");
		glUniform4f(location, 1.0f, 0.0f, 0.0f, 1.0f);

		location = glGetUniformLocation(shader, "u_MVP");
		glUniformMatrix4fv(location, 1, GL_FALSE, &mvp[0][0]);

		// this one encapsulate into another class
		glDrawArrays(GL_POINTS, 0, 1);
	}

	void DrawWireFrameQuad(int xpos, int ypos, int xsize, int ysize)
	{
		GLfloat positions[] =
		{
			-0.5f, -0.5f, // 0
			0.5f , -0.5f, // 1
			0.5f , 0.5f,  // 2
			-0.5f, 0.5f   // 3
		};


		GLuint indices[] =
		{
			0,1,2,
			2,3,0
		};

		VertexBuffer vbo(positions, 4 * 2 * sizeof(GLfloat)); // bind vbo, bind, ebo must bind every single loop
		ElementBuffer ebo(indices, 6);

		glEnableVertexAttribArray(0);

		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

		int windowWidth = 800;
		int windowHeight = 600;

		glm::mat4 proj = glm::ortho(-(float)windowWidth / 2, (float)windowWidth / 2, -(float)windowHeight / 2, (float)windowHeight / 2);

		std::string vertexShader =
			"#version 330 core\n"
			"uniform mat4 u_MVP;\n"
			"layout(location = 0) in vec4 position;"
			"\n"
			"void main()\n"
			"{\n"
			"gl_Position = u_MVP * position;\n"
			"}\n";

		std::string fragmentShader =
			"#version 330 core\n"
			"layout(location = 0) out vec4 color;"
			"uniform vec4 u_Color;\n"
			"void main()\n"
			"{\n"
			"color = u_Color;\n"
			"}\n";

		GLuint shader = CreateShader(vertexShader, fragmentShader);
		glUseProgram(shader);

		glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(xpos, ypos, 0));
		glm::mat4 rotate = glm::rotate(glm::mat4(1.0f), objList[0]._angle, glm::vec3(0, 0, 1));
		glm::mat4 model = translate * glm::scale(glm::mat4(1.0f), glm::vec3(xsize, ysize, 1.0f));

		glm::mat4 mvp = proj * model;

		int location = glGetUniformLocation(shader, "u_Color");
		glUniform4f(location, 1.0f, 0.0f, 0.0f, 1.0f);

		location = glGetUniformLocation(shader, "u_MVP");
		glUniformMatrix4fv(location, 1, GL_FALSE, &mvp[0][0]);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		// this one encapsulate into another class
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
	}
	void DrawLine(int x1, int y1, int x2, int y2)
	{
		int windowWidth = 800;
		int windowHeight = 600;

		glm::mat4 proj = glm::ortho(-(float)windowWidth / 2, (float)windowWidth / 2, -(float)windowHeight / 2, (float)windowHeight / 2);

		std::string vertexShader =
			"#version 330 core\n"
			"uniform mat4 u_MVP;\n"
			"layout(location = 0) in vec4 position;"
			"\n"
			"void main()\n"
			"{\n"
			"gl_Position = u_MVP * position;\n"
			"}\n";

		std::string fragmentShader =
			"#version 330 core\n"
			"layout(location = 0) out vec4 color;"
			"uniform vec4 u_Color;\n"
			"void main()\n"
			"{\n"
			"color = u_Color;\n"
			"}\n";

		GLuint shader = CreateShader(vertexShader, fragmentShader);
		glUseProgram(shader);


		int x = (x1 + x2) / 2;
		int y = (y1 + y2) / 2;

		glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
		glm::mat4 mvp = proj * model;

		int location = glGetUniformLocation(shader, "u_Color");
		glUniform4f(location, 1.0f, 0.0f, 0.0f, 1.0f);

		location = glGetUniformLocation(shader, "u_MVP");
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
};