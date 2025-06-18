#ifndef VERTEXBUFFER_HPP
#define VERTEXBUFFER_HPP

class VertexBuffer {
private:
	unsigned int m_RendererID = 0;
public:
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;

};

#endif //VERTEXBUFFER_HPP