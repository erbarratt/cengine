#ifndef VERTEXBUFFER_HPP
#define VERTEXBUFFER_HPP

namespace MM
{
	class VertexBuffer {
	public:
		unsigned int m_RendererID = 0;
		VertexBuffer(const void* data, unsigned int size);
		~VertexBuffer();

		void bind() const;
		void unbind() const;

	};
}

#endif //VERTEXBUFFER_HPP