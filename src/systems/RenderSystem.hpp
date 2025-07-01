#ifndef RENDERSYSTEM_HPP
#define RENDERSYSTEM_HPP

#include "../core/System.hpp"
#include "GLM/glm.hpp"

namespace MM
{
	class RenderSystem : System {
		public:
			RenderSystem();
			void Render(glm::mat4 projection, glm::mat4 view);
	};
}

#endif //RENDERSYSTEM_HPP
