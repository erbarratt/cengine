#ifndef MESH_HPP
#define MESH_HPP

#pragma once

struct Mesh
{
	float * positions;
	unsigned int positionsSize;
	unsigned int * indices;
	unsigned int indicesCount;
	unsigned int vbo_id;
	unsigned int ibo_id;
	unsigned int vao_id;
};

#endif //MESH_HPP
