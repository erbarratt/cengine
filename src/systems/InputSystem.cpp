#include "InputSystem.hpp"
#include "../components/Input.hpp"

namespace MM {

	void InputSystem::Update(GLFWwindow *window)
	{

		Input input;
		input.w = glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS;
		input.a = glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS;
		input.s = glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS;
		input.d = glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS;
		input.up = glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS;
		input.down = glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS;
		input.left = glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS;
		input.right = glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS;

		for (auto const& entity : mEntities)
		{
			auto& inputSettings = gCoordinator.GetComponent<Input>(entity);
			inputSettings = input;
		}

	}

} // MM