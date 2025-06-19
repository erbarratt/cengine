//
// Created by ellio on 19/06/2025.
//

#ifndef VERTEXARRAY_HPP
#define VERTEXARRAY_HPP



class VertexArray {
	private:
		unsigned int m_RendererID = 0;
		unsigned int currentIndex = 0;
	public:
		VertexArray();
		void bind() const;
		void unbind() const;
		void addVertexAttribPointer(int size, int type, int stride, const void *offset);
};



#endif //VERTEXARRAY_HPP
