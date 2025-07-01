#include "RenderSystem.hpp"

#include "../render/GLDebug.h"

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

		CGL(glClear(GL_COLOR_BUFFER_BIT));

		for (auto const& entity : mEntities)
		{
			auto& mesh = gCoordinator.GetComponent<Mesh>(entity);
			auto& material = gCoordinator.GetComponent<Material>(entity);
			const auto& transform = gCoordinator.GetComponent<Transform>(entity);

			//VBO
				//tell opengl we are now using the specified buffer object (by passing the id previously generated)
				//IN the "target" type we specify, GL_ARRAY_BUFFER = Vertex Attributes
				CGL(glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo_id));

			//IBO
				//tell opengl we are now using the specified buffer object (by passing the id previously generated)
				//IN the "target" type we specify, GL_ARRAY_BUFFER = Vertex Attributes
				CGL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.ibo_id));

				//fill the currently bound buffer at the "target" with "size" bytes from a data object and hint at how it will be used
				CGL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.indicesCount * sizeof(unsigned int), mesh.indices, GL_STATIC_DRAW));

			//VAO
				//tell opengl we are now using the specified ARRAY object (by passing the id previously generated)
				CGL(glBindVertexArray(mesh.vao_id));

			//shader
				CGL(glUseProgram(material.shaderProgram));

			//texture
				CGL(glActiveTexture(GL_TEXTURE0 + 0));
				CGL(glBindTexture(GL_TEXTURE_2D, material.textureId));

				CGL(glUniform1i(glGetUniformLocation(material.shaderProgram, "u_texture"), 0));

			//projections
				glm::mat4 matrix = projection * view * glm::translate(glm::mat4(1.0f), glm::vec3(transform.position.x, transform.position.y, transform.position.z) );
				CGL(glUniformMatrix4fv(glGetUniformLocation(material.shaderProgram, "u_MVP"), 1, GL_FALSE, &matrix[0][0]));

			//finally draw now state set
				CGL(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

		}

	}


}