#include "TTK/MeshBase.h"
#include "GLUT/glut.h"
#include <iostream>

void TTK::MeshBase::draw()
{
	vbo.draw();
}

void TTK::MeshBase::draw_1_0()
{
	if (vertices.size() == 0)
	{
		std::cout << "Mesh has no vertices!" << std::endl;
		return;
	}

	bool useColours = colours.size() > 0 ? true : false;
	bool useUVs = textureCoordinates.size() > 0 ? true : false;

	if (useUVs)
	{
		if (textureCoordinates.size() != vertices.size())
		{
			std::cout << "Number of texture coordinates does not match number of vertices!" << std::endl;
			return;
		}
	}

	if (useColours)
	{
		if (colours.size() != vertices.size())
		{
			std::cout << "Number of vertex colours does not match number of vertices!" << std::endl;
			return;
		}
	}

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_ADD);

	if (primitiveType == TTK::PrimitiveType::Quads)
		glBegin(GL_QUADS);
	else
		glBegin(GL_TRIANGLES);

	for (unsigned int i = 0; i < vertices.size(); i++)
	{
		glTexCoord2f(textureCoordinates[i].x, textureCoordinates[i].y);

		if (useColours)
			glColor4fv(&colours[i][0]);
		else
			glColor4f(0.0, 0.0, 0.0, 1.0);

		glNormal3fv(&normals[i][0]);
		glVertex3fv(&vertices[i][0]);
	}

	glEnd();

	glDisable(GL_BLEND);
}

void TTK::MeshBase::setAllColours(glm::vec4 colour)
{
	for (unsigned int i = 0; i < colours.size(); i++)
	{
		colours[i] = colour;
	}
}
