#include "RenderableSystem.hpp"

#include "../core/Coordinator.hpp"

#include "../components/Mesh.hpp"
#include "../components/Material.hpp"

extern Coordinator gCoordinator;

namespace MM {

	void RenderableSystem::SetMesh(unsigned plane, const float *positions, const unsigned int *indices)
	{

		//vert buffer layout
		VertexBufferLayout vbl;
		vbl.Push(GL_FLOAT, 2, false);
		vbl.Push(GL_FLOAT, 2, false);

		gCoordinator.AddComponent<Mesh>(plane, Mesh{
			VertexBuffer(positions, 4 * 4 * sizeof(float)).m_RendererID,
			vbl,
			IndexBuffer (indices, 6),
			VertexArray()
		});

		auto& meshSettings = gCoordinator.GetComponent<Mesh>(plane);
		meshSettings.vao.addBuffer(meshSettings.vbo, meshSettings.vbl);
	}

	void RenderableSystem::SetMaterial(unsigned plane, const char *shaderName, const char *textureName)
	{
		gCoordinator.AddComponent<Material>(plane, Material{
			Shader (shaderName),
			Texture(textureName)
		});
	}
} // MM