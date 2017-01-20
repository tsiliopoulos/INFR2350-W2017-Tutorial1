#pragma once
#include <string>
#include "GLEW/glew.h"

class Shader // program that runs on the GPU
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