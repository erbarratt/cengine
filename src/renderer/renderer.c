#include "../../external/glad/include/glad/gl.h"
#include "renderer.h"
#include "glfw3.h"

void renderer_init() {
	gladLoadGL(glfwGetProcAddress);
	glEnable(GL_DEPTH_TEST);
}

void renderer_clear() {
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void renderer_draw() {
	// Eventually draw a triangle/VAO here
}