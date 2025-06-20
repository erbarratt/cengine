#pragma once

#include <GLEW/glew.h>

#include "IndexBuffer.hpp"
#include "VertexArray.hpp"
#include "VertexBuffer.hpp"
#include "Shader.hpp"

#ifndef RENDERER_HPP
#define RENDERER_HPP

namespace MarMyte
{
class Renderer
{
	public:
		void draw(const VertexArray& va, const IndexBuffer& ib, const VertexBuffer& vb, const Shader& shader);
	private:
};
}

#endif //RENDERER_HPP