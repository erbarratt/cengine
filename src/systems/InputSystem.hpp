#ifndef INPUTSYSTEM_HPP
#define INPUTSYSTEM_HPP

#include "../core/Coordinator.hpp"
#include "../core/System.hpp"

#include "GLFW/glfw3.h"

extern Coordinator gCoordinator;

namespace MM {

	class InputSystem : public System
	{
		public:
			void Update(GLFWwindow *window);
	};

} // MM

#endif //INPUTSYSTEM_HPP
