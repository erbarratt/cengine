#ifndef VERTEXBUFFER_HPP
#define VERTEXBUFFER_HPP

namespace MarMyte
{
	class VertexBuffer {
	private:
		unsigned int m_RendererID = 0;
	public:
		VertexBuffer(const void* data, unsigned int size);
		~VertexBuffer();

		void bind() const;
		void unbind() const;

	};
}

#endif //VERTEXBUFFER_HPP