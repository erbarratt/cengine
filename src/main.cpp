#include <iostream>
#include <GLEW/glew.h>
#include <GLFW/glfw3.h>

static unsigned int compileShader(unsigned int type, const std::string& source)
{
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE) {
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length);
		glGetShaderInfoLog(id, length, &length, message);
		std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertext" : "fragment") << " shader!" << std::endl;
		std::cout << message << std::endl;
		glDeleteShader(id);
		return 0;
	}

	return id;
}

static unsigned int createShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	unsigned int program = glCreateProgram();
	unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

	glAttachShader(program, vs);
	glAttachShader(program, fs);

	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}

int main()
{
	//Initialize GLFW
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	GLFWwindow *window = glfwCreateWindow(640, 480, "Hello World", nullptr, nullptr);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK) {
		std::cout << "Failed to initialize GLEW" << std::endl;
	}

	std::cout << glGetString(GL_VERSION) << std::endl;

	float positions[6] = {
		-0.5f, -0.5f,
		0.0f, 0.5f,
		0.5f, -0.5f
	};

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

	//define the shader src
	std::string vertexShader =
		"#version 330 core\n"
		"layout (location = 0) in vec4 position;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = position;\n"
		"}\n";

	std::string fragmentShader =
		"#version 330 core\n"
		"layout (location = 0) out vec4 color;\n"
		"void main()\n"
		"{\n"
		"   color = vec4(1.0, 0.0, 0.0, 1.0);\n"
		"}\n";

	unsigned int shaderProgram = createShader(vertexShader, fragmentShader);
	glUseProgram(shaderProgram);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawArrays(GL_TRIANGLES, 0, 3);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}