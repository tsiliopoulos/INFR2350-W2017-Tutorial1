#include "ShaderProgram.h"
#include <iostream>

ShaderProgram::ShaderProgram()
{
	handle = 0;
}

ShaderProgram::~ShaderProgram()
{
	destroy();
}

void ShaderProgram::attachShader(Shader shader)
{
	// CODE HERE /////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
}

int ShaderProgram::linkProgram()
{
	if (handle)
	{
		// CODE HERE /////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////
	}
	else
	{
		std::cout << "Shader program failed to link: handle not set" << std::endl;
	}
	return 0; 
}

void ShaderProgram::bind()
{
	// CODE HERE /////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
}

void ShaderProgram::unbind()
{
	// CODE HERE /////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
}

void ShaderProgram::sendUniformInt(const std::string& uniformName, int intVal)
{
	// CODE HERE /////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
}

void ShaderProgram::sendUniformVec4(const std::string& uniformName, glm::vec4& vec4)
{
	// CODE HERE /////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
}

void ShaderProgram::sendUniformMat4(const std::string& uniformName, glm::mat4& mat4)
{
	// CODE HERE /////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
}

void ShaderProgram::destroy()
{
	// CODE HERE /////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
}

int ShaderProgram::getUniformLocation(const std::string& uniformName)
{
	// CODE HERE /////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	return -1; // REMOVE THIS LINE
}