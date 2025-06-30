//
// Created by ellio on 25/06/2025.
//

#ifndef VERTEXBUFFERLAYOUT_HPP
#define VERTEXBUFFERLAYOUT_HPP
#include <vector>
#include <GLEW/glew.h>

namespace MM {

struct VertexBufferElement
{
	int type;
	int count;
	bool normalized;
};

class VertexBufferLayout {

private:
	std::vector<VertexBufferElement> elements;
	int stride;

public:
	VertexBufferLayout()
		:stride(0) {}

	static int getSizeOfType(int type);

	void Push(int type, int count, bool normalised);

	[[nodiscard]] inline const std::vector<VertexBufferElement>& getElements() const { return elements; }
	[[nodiscard]] inline const int& getStride() const { return stride; }

};

} // MarMyte

#endif //VERTEXBUFFERLAYOUT_HPP
