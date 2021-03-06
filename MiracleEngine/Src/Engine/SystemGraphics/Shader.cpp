#include "Shader.h"
#include "PrecompiledHeaders.h"

void Shader::SetUniform1i(const std::string& name, int value)
{
	int location = glGetUniformLocation(_id, name.c_str());
	glUniform1i(location, value);
}

void Shader::SetUniform1f(const std::string& name, float value)
{
	int location = glGetUniformLocation(_id, name.c_str());
	glUniform1f(location, value);
}

void Shader::Select() const
{
	glUseProgram(_id);
}


void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3) const
{
	int location = glGetUniformLocation(_id, name.c_str());
	glUniform4f(location, v0, v1, v2, v3);
}

void Shader::SetUniformMat4f(const std::string& name, const glm::mat4& matrix) const
{
	int location = glGetUniformLocation(_id, name.c_str());
	glUniformMatrix4fv(location, 1, GL_FALSE, &matrix[0][0]);
}

int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	//generate shader buffer id
	_id = glCreateProgram();

	CompileShader(GL_VERTEX_SHADER, vertexShader);
	return 0;
}


GLuint Shader::CompileShader(GLuint type, const std::string& source) const
{
	///read the source code for the type of shader into the GPU
	GLuint vs = glCreateShader(type);
	return 0;
}

bool Shader::load(std::string vert, std::string frag)
{
	int success;
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
	// ensure ifstream objects can throw exceptions:
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		// open files
		vShaderFile.open(vert);
		fShaderFile.open(frag);
		std::stringstream vShaderStream, fShaderStream;
		// read file's buffer contents into streams
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		// close file handlers
		vShaderFile.close();
		fShaderFile.close();
		// convert stream into string
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
		return false;
	}
	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();

	// vertex Shader
	GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << std::endl;
		return false;
	};
	// fragment Shader
	GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	// print compile errors if any
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		std::cout << "ERROR::SHADER::FRAG::COMPILATION_FAILED\n" << std::endl;
		return false;
	};

	_id = glCreateProgram();
	glAttachShader(_id, vertex);
	glAttachShader(_id, fragment);
	glLinkProgram(_id);
	// print linking errors if any
	glGetProgramiv(_id, GL_LINK_STATUS, &success);
	if (!success)
	{
		//glGetProgramInfoLog(ID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << std::endl;
		return false;
	}

	glValidateProgram(_id);

	glDeleteShader(vertex);
	glDeleteShader(fragment);

	return true;
}

void Shader::unload()
{
	glDeleteProgram(_id);
}
