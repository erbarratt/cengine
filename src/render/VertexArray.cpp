#include "VertexArray.hpp"

#include "VertexBuffer.hpp"
#include "VertexBufferLayout.hpp"
#include "GLEW/glew.h"

namespace MM
{
	VertexArray::VertexArray()
	{
		//generate n buffer "names" or "ids" stored as integers into the mem location provided
		glGenVertexArrays(1, &VAO_id);

		//tell opengl we are now using the specified ARRAY object (by passing the id previously generated)
		glBindVertexArray(VAO_id);
	}

	VertexArray::~VertexArray()
	{
		glDeleteVertexArrays(1, &VAO_id);
	}

	void VertexArray::bind() const
	{
		//tell opengl we are now using the specified ARRAY object (by passing the id previously generated)
		glBindVertexArray(VAO_id);
	}

	void VertexArray::unbind()
	{
		glBindVertexArray(0);
	}

	void VertexArray::addBuffer(const VertexBuffer& vertexBuffer, const VertexBufferLayout& layout)
	{
		vertexBuffer.bind();
		const auto& elements = layout.getElements();
		int offset = 0;
		for (const auto& element : elements) {
			//enable a vertex attribute by index ++OF THE VERTEXX ARRAY OBJECT++, for defining below...
			glEnableVertexAttribArray(currentIndex);

			//define the structure of our vertex attributes - in this case just a vec2 list of x,y coords.
			//this vertex attributes has an index or "id" of 0 ++OF THE VERTEXX ARRAY OBJECT++
			//is comprised of "size" 2 things of "type" float
			//we have already normalised the data
			//to get to the same attrib of the next vertex, we need to move along "stride" bytes.
			//to get to this attribute in the first vertex, how many bytes (as a void*) do we need to move along the data?
			glVertexAttribPointer(currentIndex, element.count, element.type, element.normalized, layout.getStride(), reinterpret_cast<const void *>(offset));

			offset += element.count * VertexBufferLayout::getSizeOfType(element.type);

			currentIndex++;
		}
	}
}