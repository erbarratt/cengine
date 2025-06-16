#include "../../external/glfw/include/glfw3.h"
#include "window.h"

static GLFWwindow* window;

uint8_t window_init(const int width, const int height, const char* title) {

	//init th glfw lib
	if (!glfwInit()) return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(width, height, title, NULL, NULL);
	if (!window) return -1;

	glfwMakeContextCurrent(window);
	return 0;

}

void window_poll() {
	glfwSwapBuffers(window);
	glfwPollEvents();
}

int window_should_close() {
	return glfwWindowShouldClose(window);
}