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

	// CODE HERE (implement shader loading / compiling) //////////////////////
	//////////////////////////////////////////////////////////////////////////

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

