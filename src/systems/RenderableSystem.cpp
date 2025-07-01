#include "RenderableSystem.hpp"

#include "../components/Mesh.hpp"
#include "../components/Material.hpp"

namespace MM {

	void RenderableSystem::SetMesh(unsigned plane, float *positions, unsigned int *indices)
	{

		//VBO
		VertexBuffer vbo(positions, 4 * 4 * sizeof(float));

		//vert buffer layout
		VertexBufferLayout vbl;
		vbl.Push(GL_FLOAT, 2, false);
		vbl.Push(GL_FLOAT, 2, false);

		VertexArray vao({});
		vao.addBuffer(vbo, vbl);

		IndexBuffer ibo(indices, 6);

		gCoordinator.AddComponent<Mesh>(plane, Mesh{
			positions,
			4 * 4 * sizeof(float),
			indices,
			6,
			vbo.m_RendererID,
			ibo.GetRendererID(),
			vao.VAO_id
		});

	}

	void RenderableSystem::SetMaterial(unsigned plane, const char *shaderName, const char *textureName)
	{
		gCoordinator.AddComponent<Material>(plane, Material{
			Shader (shaderName).program,
			Texture (textureName).textureId
		});
	}
} // MM