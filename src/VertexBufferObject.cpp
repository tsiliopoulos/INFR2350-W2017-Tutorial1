#include "VertexBufferObject.h"
#include <iostream>

VertexBufferObject::VertexBufferObject()
{
	vaoHandle = 0;
}

VertexBufferObject::~VertexBufferObject()
{
	destroy();
}

int VertexBufferObject::addAttributeArray(AttributeDescriptor attrib)
{
	attributeDescriptors.push_back(attrib);
	return 1;
}

void VertexBufferObject::createVBO()
{
	// CODE HERE /////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
}

void VertexBufferObject::draw()
{
	// CODE HERE /////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
}

void VertexBufferObject::destroy()
{
	if (vaoHandle)
	{
		glDeleteVertexArrays(1, &vaoHandle);
		glDeleteBuffers(vboHandles.size(), &vboHandles[0]);
	}

	vboHandles.clear();
	attributeDescriptors.clear();
}


