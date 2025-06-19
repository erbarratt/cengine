//
// Created by ellio on 19/06/2025.
//

#include "VertexArray.hpp"

#include "GLEW/glew.h"

VertexArray::VertexArray()
{
	//generate n buffer "names" or "ids" stored as integers into the mem location provided
	glGenVertexArrays(1, &m_RendererID);

	//tell opengl we are now using the specified ARRAY object (by passing the id previously generated)
	glBindVertexArray(m_RendererID);
}

void VertexArray::bind() const
{
	//tell opengl we are now using the specified ARRAY object (by passing the id previously generated)
	glBindVertexArray(m_RendererID);
}

void VertexArray::unbind() const
{
	glBindVertexArray(0);
}

void VertexArray::addVertexAttribPointer(int size, int type, int stride, const void* offset)
{
	//enable a vertex attribute by index ++OF THE VERTEXX ARRAY OBJECT++, for defining below...
	glEnableVertexAttribArray(currentIndex);

	//define the structure of our vertex attributes - in this case just a vec2 list of x,y coords.
	//this vertex attributes has an index or "id" of 0 ++OF THE VERTEXX ARRAY OBJECT++
	//is comprised of "size" 2 things of "type" float
	//we have already normalised the data
	//to get to the same attrib of the next vertex, we need to move along "stride" bytes.
	//to get to this attribute in the first vertex, how many bytes (as a void*) do we need to move along the data?
	glVertexAttribPointer(currentIndex, size, type, GL_FALSE, stride, offset);

	currentIndex++;

}
