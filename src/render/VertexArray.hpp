//
// Created by ellio on 19/06/2025.
//

#ifndef VERTEXARRAY_HPP
#define VERTEXARRAY_HPP
#include "VertexBuffer.hpp"
#include "VertexBufferLayout.hpp"

namespace MarMyte
{
	class VertexArray {
	private:
		unsigned int VAO_id = 0;
		unsigned int currentIndex = 0;
	public:
		VertexArray();
		~VertexArray();
		void bind() const;
		static void unbind() ;
		void addBuffer(const VertexBuffer &vertexBuffer, const MarMyte::VertexBufferLayout &layout);
	};
}

#endif //VERTEXARRAY_HPP
