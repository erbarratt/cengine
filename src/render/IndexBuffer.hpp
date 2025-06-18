#ifndef INDEXBUFFER_HPP
#define INDEXBUFFER_HPP

class IndexBuffer {
private:
	unsigned int m_RendererID = 0;
	unsigned int m_IndexCount = 0;
public:
	IndexBuffer(const void* data, unsigned int count);
	~IndexBuffer();

	void Bind() const;
	void Unbind() const;

	inline unsigned int GetRendererID() const { return m_RendererID; }
	inline unsigned int GetCount() const { return m_IndexCount; }

};

#endif //INDEXBUFFER_HPP