#include "Shader.h"
#include <iostream>
#include "GLEW/glew.h"
#include "TTK/io.h"

Shader::Shader()
{
	handle = 0;
}

Shader::~Shader()
{
	destroy();
}

unsigned int Shader::loadShaderFromFile(std::string fileName, GLenum type)
{
	// Load shader file into memory
	std::string shaderCode = TTK::IO::loadFile(fileName).c_str();

	// Could not load file
	if (shaderCode.length() == 0)
		return 0;

	handle = glCreateShader(type);

	const char* cstr = shaderCode.c_str();

	glShaderSource(handle, 1, &cstr, 0);

	glCompileShader(handle);

	int compileStatus;

	glGetShaderiv(handle, GL_COMPILE_STATUS, &compileStatus);

	if (compileStatus) {
		std::cout << "Shader compiled successfully: " << fileName << std::endl;
		return handle;
	}

	std::cout << "Shader failed to compile: " << fileName << std::endl;

	int logLength;
	glGetShaderiv(handle, GL_INFO_LOG_LENGTH, &logLength);

	std::string log(logLength, ' ');

	glGetShaderInfoLog(handle, logLength, &logLength, &log[0]);

	std::cout << log << std::endl;

	return 0;
}

void Shader::destroy()
{
	// If handle is zero it means the shader does not exist
	if (handle)
	{
		// Frees memory occupied by this shader
		glDeleteShader(handle);
		handle = 0;
	}
}

