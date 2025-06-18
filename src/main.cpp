#include <iostream>
#include <GLEW/glew.h>
#include <GLFW/glfw3.h>

#include "render/Shaders.hpp"

int main()
{
	//Initialize GLFW
	if (!glfwInit())
		return -1;

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

	//vertex buffer
		unsigned int buffer;

		//generate n buffer "names" or "ids" stored as integers into the mem location provided
		//remember an array without an index is the pointer, so "buffers" but a single uint would need to pass the pointer, so &buffer
		glGenBuffers(1, &buffer);

		//tell opengl we are now using the specified buffer object (by passing the id previously generated)
		//IN the "target" type we specify, GL_ARRAY_BUFFER = Vertex Attributes
		glBindBuffer(GL_ARRAY_BUFFER, buffer);

		//fill the currently bound buffer at the "target" with "size" bytes from a data object and hint at how it will be used
		glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);

		//enable a vertex attribute by index, for defining below...
		glEnableVertexAttribArray(0);

		//define the structure of our vertex attributes - in this case just a vec2 list of x,y coords.
		//this vertex attributes has an index or "id" of 0, is comprised of "size" 2 things of "type" float
		//we have already normalised the data
		//to get to the same attrib of the next vertex, we need to move along "stride" bytes.
		//to get to this attribute in the first vertex, how many bytes (as a void*) do we need to move along the data?
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);

	//index buffer
		unsigned int indexBuffer;
		//generate n buffer "names" or "ids" stored as integers into the mem location provided
		//remember an array without an index is the pointer, so "buffers" but a single uint would need to pass the pointer, so &buffer
		glGenBuffers(1, &indexBuffer);

		//tell opengl we are now using the specified buffer object (by passing the id previously generated)
		//IN the "target" type we specify, GL_ARRAY_BUFFER = Vertex Attributes
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

		//fill the currently bound buffer at the "target" with "size" bytes from a data object and hint at how it will be used
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


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
