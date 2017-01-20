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
	if (handle == 0) {
		handle = glCreateProgram();
	}

	if (shader.getHandle()) {
		glAttachShader(handle, shader.getHandle());
	}
}

int ShaderProgram::linkProgram()
{
	if (handle)
	{
		glLinkProgram(handle);

		int linkStatus;
		glGetProgramiv(handle, GL_LINK_STATUS, &linkStatus);

		if (linkStatus) {
			std::cout << "Shader linked successfully" << std::endl;
			return handle;
		}

		int logLength;
		glGetProgramiv(handle, GL_INFO_LOG_LENGTH, &logLength);

		std::string log(logLength, ' ');
		glGetProgramInfoLog(handle, logLength, &logLength, &log[0]);
		std::cout << log << std::endl;
	}
	else
	{
		std::cout << "Shader program failed to link: handle not set" << std::endl;
	}
	return 0; 
}

void ShaderProgram::bind()
{
	glUseProgram(handle);
}

void ShaderProgram::unbind()
{
	glUseProgram(0);
}

void ShaderProgram::sendUniformInt(const std::string& uniformName, int intVal)
{
	int uniformLocation = getUniformLocation(uniformName);
	glUniform1i(uniformLocation, intVal);
}

void ShaderProgram::sendUniformVec4(const std::string& uniformName, glm::vec4& vec4)
{
	int uniformLocation = getUniformLocation(uniformName);
	glUniform4fv(uniformLocation, 1, &vec4[0]);
}

void ShaderProgram::sendUniformMat4(const std::string& uniformName, glm::mat4& mat4)
{
	int uniformLocation = getUniformLocation(uniformName);
	glUniformMatrix4fv(uniformLocation, 1, false, &mat4[0][0]);
}

void ShaderProgram::destroy()
{
	if (handle) {
		glDeleteProgram(handle);
		handle = 0;
	}
}

int ShaderProgram::getUniformLocation(const std::string& uniformName)
{
	return glGetUniformLocation(handle, uniformName.c_str());
}
