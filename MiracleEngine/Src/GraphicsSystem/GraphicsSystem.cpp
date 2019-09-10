#include "GraphicsSystem.h"

#include <string>

GLuint CompileShader(const std::string& source, GLuint type)
{
	GLuint id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	// TODO:: error handling

	return id;
}


GLuint CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	GLuint program = glCreateProgram();
	GLuint vs = CompileShader(vertexShader, GL_VERTEX_SHADER);
	GLuint fs = CompileShader(fragmentShader, GL_FRAGMENT_SHADER);

	glAttachShader(program, vs);
	glAttachShader(program, fs);

	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}

void GraphicsSystem::Init()
{


	//GAME_ENGINE::Init();

	glewInit();


}
void GraphicsSystem::Update()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glClearColor(.0f, .0f, .0f, 1.0f);


	/*glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_TRIANGLES);
	glVertex2f(-0.5f, -0.5f);
	glVertex2f(-0.0f, 0.5f);
	glVertex2f(0.5f, -0.5f);
	glEnd();*/

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

	VertexBuffer vbo(positions, 4 * 2 * sizeof(GLfloat));
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

	glClear(GL_COLOR_BUFFER_BIT);

	glClearColor(.0f, .0f, .0f, 1.0f);



	glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
	glm::mat4 model = translate * glm::scale(glm::mat4(1.0f), glm::vec3(100, 100, 1.0f));

	glm::mat4 mvp = proj * model;

	int location = glGetUniformLocation(shader, "u_Color");
	glUniform4f(location, 1.0f, 0.0f, 0.0f, 1.0f);

	location = glGetUniformLocation(shader, "u_MVP");
	glUniformMatrix4fv(location, 1, GL_FALSE, &mvp[0][0]);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}
void GraphicsSystem::Exit()
{

}