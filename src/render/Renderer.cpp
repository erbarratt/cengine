#include "Renderer.hpp"

namespace MarMyte
{
	Renderer::Renderer()
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void Renderer::draw(const VertexArray &va, const IndexBuffer &ib, const VertexBuffer &vb, const Shader &shader)
	{

		va.bind();
		ib.bind();
		vb.bind();
		shader.bind();

		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
	}


}

