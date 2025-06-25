//
// Created by ellio on 25/06/2025.
//

#include "VertexBufferLayout.hpp"

namespace MarMyte {
	unsigned int VertexBufferLayout::getSizeOfType(unsigned int type)
	{
		switch (type) {
			case GL_FLOAT:
			case GL_UNSIGNED_INT:
				return 4;
			case GL_UNSIGNED_BYTE:
				return 1;
			default:
				return 1;
		}
	}

	void VertexBufferLayout::Push(const unsigned int type, const unsigned int count, const bool normalised)
	{
		elements.push_back({ type, count, normalised });
		stride += count * VertexBufferLayout::getSizeOfType(type);
	}
} // MarMyte