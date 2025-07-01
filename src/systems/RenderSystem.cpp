#include "RenderSystem.hpp"

#include "../core/Coordinator.hpp"

#include "../components/Transform.hpp"
#include "../components/Mesh.hpp"
#include "../components/Material.hpp"
#include "GLM/ext/matrix_transform.hpp"

extern Coordinator gCoordinator;

namespace MM
{
	RenderSystem::RenderSystem()
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void RenderSystem::Render(glm::mat4 projection, glm::mat4 view)
	{

		glClear(GL_COLOR_BUFFER_BIT);

		for (auto const& entity : mEntities)
		{
			auto& mesh = gCoordinator.GetComponent<Mesh>(entity);
			auto& material = gCoordinator.GetComponent<Material>(entity);
			const auto& transform = gCoordinator.GetComponent<Transform>(entity);

			mesh.vao.bind();
			mesh.ibo.bind();
			mesh.vbo.bind();
			material.shader.bind();
			material.texture.bind();

			material.shader.setUniformi("u_texture", 0);

			material.shader.setUniformMat4f("u_MVP", projection * view * glm::translate(glm::mat4(1.0f), glm::vec3(transform.position.x, transform.position.y, transform.position.z) ) );

			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

		}

	}


}