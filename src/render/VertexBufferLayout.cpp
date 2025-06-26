//
// Created by ellio on 25/06/2025.
//

#include "VertexBufferLayout.hpp"

namespace MarMyte {
	int VertexBufferLayout::getSizeOfType(int type)
	{
		switch (type) {
			case GL_FLOAT:
			case GL_UNSIGNED_INT:
				return 4;
			case GL_UNSIGNED_BYTE:
			default:
				return 1;
		}
	}

	void VertexBufferLayout::Push(const int type, const int count, const bool normalised)
	{
		elements.push_back({ type, count, normalised });
		stride += count * getSizeOfType(type);
	}
} // MarMyte