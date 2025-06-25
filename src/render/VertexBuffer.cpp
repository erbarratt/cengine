#include "VertexBuffer.hpp"

#include "GLEW/glew.h"

namespace MarMyte
{
	VertexBuffer::VertexBuffer(const void* data, unsigned int size)
	{

		//generate n buffer "names" or "ids" stored as integers into the mem location provided
		//remember an array without an index is the pointer, so "buffers" but a single uint would need to pass the pointer, so &buffer
		glGenBuffers(1, &m_RendererID);

		//tell opengl we are now using the specified buffer object (by passing the id previously generated)
		//IN the "target" type we specify, GL_ARRAY_BUFFER = Vertex Attributes
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);

		//fill the currently bound buffer at the "target" with "size" bytes from a data object and hint at how it will be used
		glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);

	}

	VertexBuffer::~VertexBuffer()
	{
		glDeleteBuffers(1, &m_RendererID);
	}

	void VertexBuffer::bind() const
	{
		//tell opengl we are now using the specified buffer object (by passing the id previously generated)
		//IN the "target" type we specify, GL_ARRAY_BUFFER = Vertex Attributes
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	}

	void VertexBuffer::unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}