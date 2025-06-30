#include <chrono>
#include <iostream>
#include <sstream>
#include <GLEW/glew.h>
#include <GLFW/glfw3.h>
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>

#include "components/Camera.hpp"
#include "components/Transform.hpp"
#include "render/Shader.hpp"
#include "render/Renderer.hpp"
#include "render/VertexBuffer.hpp"
#include "render/IndexBuffer.hpp"
#include "render/Texture.hpp"
#include "render/VertexArray.hpp"

#include "core/Coordinator.hpp"
#include "systems/CameraSystem.hpp"

Coordinator gCoordinator;

int main()
{

	//Initialize GLFW
	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/* Create a windowed mode window and its OpenGL context */
	GLFWwindow *window = glfwCreateWindow(800, 600, "Hello World", nullptr, nullptr);
	if (!window){ glfwTerminate(); return -1; }

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	if (glewInit() != GLEW_OK) {
		std::cout << "Failed to initialize GLEW" << std::endl;
		return -1;
	}

	std::cout << glGetString(GL_VERSION) << std::endl;

	const float positions[] = {
		-50.0f, 50.0f, 0.0f, 0.0f,
		50.0f, 50.0f, 1.0f, 0.0f,
		50.0f, -50.0f, 1.0f, 1.0f,
		-50.0f, -50.0f, 0.0f, 1.0f
	};

	const unsigned int indices[] = {
		0,1,2,
		2,3,0
	};

	//vertex array object
		MM::VertexArray vao;

	//vertex buffer object - the actual data of the vertex points
		MM::VertexBuffer vbo(positions, 4 * 4 * sizeof(float));

	//vert buffer layout
		MM::VertexBufferLayout vbl;
		vbl.Push(GL_FLOAT, 2, false);
		vbl.Push(GL_FLOAT, 2, false);

	//add buffer and layout to array object
		vao.addBuffer(vbo, vbl);

	//index buffer object
		MM::IndexBuffer ibo(indices, 6);

	//for the next draw call, use the shader program defined in this file...
		MM::Shader shader("basic");
		shader.bind();

		MM::Texture texture("../../res/textures/checker-map_tho.png");
		texture.bind();

	//projection matrixes

		gCoordinator.Init();

		gCoordinator.RegisterComponent<Camera>();
		gCoordinator.RegisterComponent<Transform>();
		auto cameraSystem = gCoordinator.RegisterSystem<MM::CameraSystem>();

		Signature signature;
		signature.set(gCoordinator.GetComponentType<Camera>());
		signature.set(gCoordinator.GetComponentType<Transform>());
		gCoordinator.SetSystemSignature<MM::CameraSystem>(signature);

		Entity camera = gCoordinator.CreateEntity();
		gCoordinator.AddComponent<Camera>(camera, Camera{
			65.0f,
			4.0f / 3.0f,
			0.1f,
			1000.0f
		});

		gCoordinator.AddComponent<Transform>(camera, Transform{
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(1.0f, 1.0f, 1.0f),
		});

		cameraSystem->SetCamera(camera);
		glm::mat4 proj = cameraSystem->GetProjectionMatrix();

		//where the camera is
		glm::vec3 camPos = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 camRot = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::mat4 view;

		//where the entity is
		glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -10.0f));

		shader.setUniformi("u_texture", 0);

	MM::Renderer renderer;

	int frameCount = 0;
	double lastTime = glfwGetTime();
	double currentTime;

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		// Measure time and update FPS counter
		currentTime = glfwGetTime();
		frameCount++;

		if (currentTime - lastTime >= 1) { // 1 second has passed
			std::ostringstream title;
			title << "OpenGL Window - FPS: " << frameCount;
			glfwSetWindowTitle(window, title.str().c_str());

			frameCount = 0;
			lastTime = currentTime;
		}

		if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
			camPos.y --;
		} else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
			camPos.y ++;
		}

		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
			camPos.x ++;
		} else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
			camPos.x --;
		}

		if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
			camRot.y --;
		} else if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
			camRot.y ++;
		}

		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
			camPos.z ++;
		} else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
			camPos.z --;
		}

		//first create a rotation matrix around the Y axis
		glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::radians(camRot.y), glm::vec3(0.0f, 1.0f, 0.0f));
		//then create a translation matrix
		glm::mat4 translate = glm::translate(glm::mat4(1.0f), camPos);
		//combine these for the resulting matrix
		view = rotation * translate;

		shader.setUniformMat4f("u_MVP", proj * view * model);

		renderer.draw(vao, ibo, vbo, shader);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
