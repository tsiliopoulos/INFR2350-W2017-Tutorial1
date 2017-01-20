#pragma once
#include <string>
#include "GLEW/glew.h"

class Shader
{
private:
	unsigned int handle;
	GLenum shaderType;

public:

	Shader();
	~Shader();

	// Returns shader handle
	unsigned int loadShaderFromFile(std::string fileName, GLenum type);

	unsigned int getHandle() { return handle; }

	void destroy();
};