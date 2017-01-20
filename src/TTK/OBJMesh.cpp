#include "TTK/OBJMesh.h"
#include "glm/glm.hpp"
#include <vector>
#include <fstream>
#include <iostream>
#include <string.h>

typedef struct
{
	int vertex1, texture1, normal1;
	int vertex2, texture2, normal2;
	int vertex3, texture3, normal3;
}Face3;

void TTK::OBJMesh::loadMesh(std::string filename)
{
	std::ifstream file;

	//open file
	file.open(filename.c_str());

	//check if file opened
	if (file.fail() == true)
	{
		std::cout << "Error - OBJMesh::loadMesh file: " << filename << " not found.\n";
		return;
	}

	char currentChar;

	glm::vec3 temp;
	Face3 temp2;

	// Containers for OBJ data
	std::vector<glm::vec3> objVertices;
	std::vector<glm::vec3> objUVs;
	std::vector<glm::vec3> objNormals;
	std::vector<Face3> objFaces;

	file.get(currentChar);

	while (!file.eof())
	{
		if (currentChar == 'v')
		{
			file.get(currentChar);
			if (currentChar == ' ')
			{
				file >> temp.x >> temp.y >> temp.z;
				objVertices.push_back(temp);
			}
			if (currentChar == 't')
			{
				file >> temp.x >> temp.y;
				temp.z = 0.0f;
				objUVs.push_back(temp);
			}
			if (currentChar == 'n')
			{
				file >> temp.x >> temp.y >> temp.z;
				objNormals.push_back(temp);
			}
		}
		else
		{
			if (currentChar == 'f')
			{
				file.get(currentChar);
				if (currentChar == ' ')
				{
					file >> temp2.vertex1 >> currentChar >> temp2.texture1 >> currentChar >> temp2.normal1;
					file >> temp2.vertex2 >> currentChar >> temp2.texture2 >> currentChar >> temp2.normal2;
					file >> temp2.vertex3 >> currentChar >> temp2.texture3 >> currentChar >> temp2.normal3;
					objFaces.push_back(temp2);
				}
			}
		}
		file.get(currentChar);
	}

	file.close();

	// Unpack data
	vertices.reserve(objVertices.size());
	normals.reserve(objNormals.size());
	textureCoordinates.reserve(objUVs.size());

	for (int i = 0; i < objFaces.size(); i++)
	{
		Face3* face = &objFaces[i];

		vertices.push_back(objVertices[face->vertex1 - 1]);
		vertices.push_back(objVertices[face->vertex2 - 1]);
		vertices.push_back(objVertices[face->vertex3 - 1]);

		normals.push_back(objNormals[face->normal1 - 1]);
		normals.push_back(objNormals[face->normal2 - 1]);
		normals.push_back(objNormals[face->normal3 - 1]);

		textureCoordinates.push_back(objUVs[face->texture1 - 1]);
		textureCoordinates.push_back(objUVs[face->texture2 - 1]);
		textureCoordinates.push_back(objUVs[face->texture3 - 1]);
	}

	numFaces = objFaces.size();

	// Setup VBO
	createVBO();
}

void TTK::OBJMesh::createVBO()
{
	// vertex
	AttributeDescriptor positionAttrib;
	positionAttrib.attributeLocation = AttributeLocations::VERTEX;
	positionAttrib.attributeName = "vertex";
	positionAttrib.data = &vertices[0];
	positionAttrib.elementSize = sizeof(float);
	positionAttrib.elementType = GL_FLOAT;

	// number of triangles * 3 vertices per triangle * 3 floats per vertex
	positionAttrib.numElements = numFaces * 3 * 3;
	positionAttrib.numElementsPerAttrib = 3;


	//  normal
	AttributeDescriptor normalAttrib;
	normalAttrib.attributeLocation = AttributeLocations::NORMAL;
	normalAttrib.attributeName = "normal";
	normalAttrib.data = &normals[0];
	normalAttrib.elementSize = sizeof(float);
	normalAttrib.elementType = GL_FLOAT;

	// number of triangles * 3 vertices per triangle * 3 floats per vertex
	normalAttrib.numElements = numFaces * 3 * 3;
	normalAttrib.numElementsPerAttrib = 3;

	//  texture
	AttributeDescriptor uvAttrib;
	uvAttrib.attributeLocation = AttributeLocations::TEX_COORD;
	uvAttrib.attributeName = "texture";
	uvAttrib.data = &textureCoordinates[0];
	uvAttrib.elementSize = sizeof(float);
	uvAttrib.elementType = GL_FLOAT;

	// number of triangles * 3 vertices per triangle * 2 floats per vertex
	uvAttrib.numElements = numFaces * 3 * 2;
	uvAttrib.numElementsPerAttrib = 2;

	vbo.addAttributeArray(positionAttrib);
	vbo.addAttributeArray(normalAttrib);
	vbo.addAttributeArray(uvAttrib);
	//... plus other attributes

	vbo.createVBO();
}

