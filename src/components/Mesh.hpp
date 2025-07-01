#ifndef MESH_HPP
#define MESH_HPP

#pragma once

#include "../render/VertexBuffer.hpp"
#include "../render/VertexBufferLayout.hpp"
#include "../render/IndexBuffer.hpp"
#include "../render/VertexArray.hpp"

struct Mesh
{
	unsigned int vbo_id;
	MM::VertexBufferLayout vbl;
	MM::IndexBuffer ibo;
	MM::VertexArray vao;
};

#endif //MESH_HPP
