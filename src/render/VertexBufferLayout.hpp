//
// Created by ellio on 25/06/2025.
//

#ifndef VERTEXBUFFERLAYOUT_HPP
#define VERTEXBUFFERLAYOUT_HPP
#include <vector>
#include <GLEW/glew.h>

namespace MarMyte {

struct VertexBufferElement
{
	unsigned int type;
	unsigned int count;
	bool normalized;
};

class VertexBufferLayout {

private:
	std::vector<VertexBufferElement> elements;
	unsigned int stride;

public:
	VertexBufferLayout()
		:stride(0) {}

	static unsigned int getSizeOfType(unsigned int type);

	void Push(unsigned int type, unsigned int count, bool normalised);

	inline const std::vector<VertexBufferElement>& getElements() const { return elements; }
	inline const unsigned int& getStride() const { return stride; }

};

} // MarMyte

#endif //VERTEXBUFFERLAYOUT_HPP
