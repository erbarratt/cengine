#include <iostream>
#include <GLEW/glew.h>
#include <GLFW/glfw3.h>

#include "render/Shaders.hpp"
#include "render/Renderer.hpp"
#include "render/VertexBuffer.hpp"
#include "render/IndexBuffer.hpp"


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

	if (glewInit() != GLEW_OK) {
		std::cout << "Failed to initialize GLEW" << std::endl;
	}

	std::cout << glGetString(GL_VERSION) << std::endl;

	const float positions[] = {
		-0.5f, -0.5f,
		0.5f, -0.5f,
		0.5f, 0.5f,
		-0.5f, 0.5f
	};

	const unsigned int indices[] = {
		0,1,2,
		2,3,0
	};

	unsigned int VAO;

	//vertexx array object
		//generate n buffer "names" or "ids" stored as integers into the mem location provided
		glGenVertexArrays(1, &VAO);

		//tell opengl we are now using the specified ARRAY object (by passing the id previously generated)
		glBindVertexArray(VAO);

	//vertex buffer object
		VertexBuffer vbo(positions, sizeof(positions));

		//enable a vertex attribute by index ++OF THE VERTEXX ARRAY OBJECT++, for defining below...
		glEnableVertexAttribArray(0);

		//define the structure of our vertex attributes - in this case just a vec2 list of x,y coords.
		//this vertex attributes has an index or "id" of 0 ++OF THE VERTEXX ARRAY OBJECT++
		//is comprised of "size" 2 things of "type" float
		//we have already normalised the data
		//to get to the same attrib of the next vertex, we need to move along "stride" bytes.
		//to get to this attribute in the first vertex, how many bytes (as a void*) do we need to move along the data?
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);

	//index buffer object
		IndexBuffer ibo(indices, 6);

	//for the next draw call, use the shader program defined in this file...
	const unsigned int program = MarMyte::Shaders::createShaderProgram("../../res/shaders/basic.shader");
	glUseProgram(program);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
