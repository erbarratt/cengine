#include <chrono>
#include <iostream>
#include <sstream>
#include <GLEW/glew.h>
#include <GLFW/glfw3.h>

#include "render/Shader.hpp"
#include "render/Renderer.hpp"
#include "render/VertexBuffer.hpp"
#include "render/IndexBuffer.hpp"
#include "render/Texture.hpp"
#include "render/VertexArray.hpp"

#include <GLM/glm.hpp>

#include "GLM/ext/matrix_clip_space.hpp"

int main()
{
	//Initialize GLFW
	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/* Create a windowed mode window and its OpenGL context */
	GLFWwindow *window = glfwCreateWindow(640, 480, "Hello World", nullptr, nullptr);
	if (!window){ glfwTerminate(); return -1; }

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	glfwSwapInterval( 0 );

	if (glewInit() != GLEW_OK) {
		std::cout << "Failed to initialize GLEW" << std::endl;
		return -1;
	}

	std::cout << glGetString(GL_VERSION) << std::endl;

	const float positions[] = {
		-0.5f, -0.5f, 0.0f, 0.0f,
		0.5f, -0.5f, 1.0f, 0.0f,
		0.5f, 0.5f, 1.0f, 1.0f,
		-0.5f, 0.5f, 0.0f, 1.0f
	};

	const unsigned int indices[] = {
		0,1,2,
		2,3,0
	};

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//vertex array object
		MarMyte::VertexArray vao;

	//vertex buffer object - the actual data of the vertex points
		MarMyte::VertexBuffer vbo(positions, 4 * 4 * sizeof(float));

	//vert buffer layout
		MarMyte::VertexBufferLayout vbl;
		vbl.Push(GL_FLOAT, 2, false);
		vbl.Push(GL_FLOAT, 2, false);

	//add buffer and layout to array object
		vao.addBuffer(vbo, vbl);

	//index buffer object
		MarMyte::IndexBuffer ibo(indices, 6);

	//projection matrix
		glm::mat4 proj = glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f, -1.0f, 1.0f);

	//for the next draw call, use the shader program defined in this file...
		MarMyte::Shader shader("../../res/shaders/basic.shader");

		MarMyte::Texture texture("../../res/textures/checker-map_tho.png");
		texture.bind();

		shader.setUniformi("u_texture", 0);

	MarMyte::Renderer renderer;

	int frameCount = 0;
	double lastTime = glfwGetTime();
	double currentTime;

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		// Measure time and update FPS counter
		currentTime = glfwGetTime();
		frameCount++;

		if (currentTime - lastTime >= 1.0) { // 1 second has passed
			std::ostringstream title;
			title << "OpenGL Window - FPS: " << frameCount;
			glfwSetWindowTitle(window, title.str().c_str());

			frameCount = 0;
			lastTime = currentTime;
		}

		renderer.draw(vao, ibo, vbo, shader);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
