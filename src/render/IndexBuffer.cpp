#include "IndexBuffer.hpp"
#include "Renderer.hpp"

IndexBuffer::IndexBuffer(const void* data, unsigned int count)
	: m_IndexCount(count)
{

	//generate n buffer "names" or "ids" stored as integers into the mem location provided
	//remember an array without an index is the pointer, so "buffers" but a single uint would need to pass the pointer, so &buffer
	glGenBuffers(1, &m_RendererID);

	//tell opengl we are now using the specified buffer object (by passing the id previously generated)
	//IN the "target" type we specify, GL_ARRAY_BUFFER = Vertex Attributes
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);

	//fill the currently bound buffer at the "target" with "size" bytes from a data object and hint at how it will be used
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);

}

IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &m_RendererID);
}

void IndexBuffer::Bind() const
{
	//tell opengl we are now using the specified buffer object (by passing the id previously generated)
	//IN the "target" type we specify, GL_ARRAY_BUFFER = Vertex Attributes
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
}

void IndexBuffer::Unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
