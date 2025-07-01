#include "RenderableSystem.hpp"
#include "../render/GLDebug.h"
#include "../render/VertexBufferLayout.hpp"
#include "../components/Mesh.hpp"
#include "../components/Material.hpp"

namespace MM {

	void RenderableSystem::SetMesh(unsigned plane, float *positions, unsigned int *indices)
	{

		//VBO
			unsigned int vbo;

			//generate n buffer "names" or "ids" stored as integers into the mem location provided
			//remember an array without an index is the pointer, so "buffers" but a single uint would need to pass the pointer, so &buffer
			CGL(glGenBuffers(1, &vbo));

			//tell opengl we are now using the specified buffer object (by passing the id previously generated)
			//IN the "target" type we specify, GL_ARRAY_BUFFER = Vertex Attributes
			CGL(glBindBuffer(GL_ARRAY_BUFFER, vbo));

			//fill the currently bound buffer at the "target" with "size" bytes from a data object and hint at how it will be used
			CGL(glBufferData(GL_ARRAY_BUFFER, 4 * 4 * sizeof(float), positions, GL_STATIC_DRAW));

		//vert buffer layout
			VertexBufferLayout vbl;
			vbl.Push(GL_FLOAT, 2, false);
			vbl.Push(GL_FLOAT, 2, false);

		//VAO
			unsigned int vao;

			//generate n buffer "names" or "ids" stored as integers into the mem location provided
			CGL(glGenVertexArrays(1, &vao));

			//tell opengl we are now using the specified ARRAY object (by passing the id previously generated)
			CGL(glBindVertexArray(vao));

			const auto& elements = vbl.getElements();
			int offset = 0;
			unsigned int currentIndex = 0;
			for (const auto& element : elements) {
				//enable a vertex attribute by index ++OF THE VERTEXX ARRAY OBJECT++, for defining below...
				CGL(glEnableVertexAttribArray(currentIndex));

				//define the structure of our vertex attributes - in this case just a vec2 list of x,y coords.
				//this vertex attributes has an index or "id" of 0 ++OF THE VERTEXX ARRAY OBJECT++
				//is comprised of "size" 2 things of "type" float
				//we have already normalised the data
				//to get to the same attrib of the next vertex, we need to move along "stride" bytes.
				//to get to this attribute in the first vertex, how many bytes (as a void*) do we need to move along the data?
				CGL(glVertexAttribPointer(currentIndex, element.count, element.type, element.normalized, vbl.getStride(), reinterpret_cast<const void *>(offset) ) );

				offset += element.count * VertexBufferLayout::getSizeOfType(element.type);

				currentIndex++;
			}

		//IBO
			unsigned int ibo;
			//generate n buffer "names" or "ids" stored as integers into the mem location provided
			//remember an array without an index is the pointer, so "buffers" but a single uint would need to pass the pointer, so &buffer
			CGL(glGenBuffers(1, &ibo));

			//tell opengl we are now using the specified buffer object (by passing the id previously generated)
			//IN the "target" type we specify, GL_ELEMENT_ARRAY_BUFFER = Vertex Indices
			CGL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo));

			//fill the currently bound buffer at the "target" with "size" bytes from a data object and hint at how it will be used
			CGL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW));

		//add component data to entity
			gCoordinator.AddComponent<Mesh>(plane, Mesh{
				positions,
				4 * 4 * sizeof(float),
				indices,
				6,
				vbo,
				ibo,
				vao
			});

	}

	void RenderableSystem::SetMaterial(unsigned plane, const char *shaderName, const char *textureName)
	{
		gCoordinator.AddComponent<Material>(plane, Material{
			Shader (shaderName).program,
			Texture (textureName).textureId
		});
	}
} //