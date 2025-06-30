#include <chrono>
#include <iostream>
#include <sstream>
#include <GLEW/glew.h>

#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>

#include "core/Window.hpp"
#include "components/Camera.hpp"
#include "components/Input.hpp"
#include "components/Transform.hpp"
#include "render/Shader.hpp"
#include "render/Renderer.hpp"
#include "render/VertexBuffer.hpp"
#include "render/IndexBuffer.hpp"
#include "render/Texture.hpp"
#include "render/VertexArray.hpp"

#include "core/Coordinator.hpp"
#include "systems/CameraSystem.hpp"
#include "systems/InputSystem.hpp"

Coordinator gCoordinator;

int main()
{

	MM::Window window;
	if (!window.Init()) {
		return -1;
	}

	if (glewInit() != GLEW_OK) {
		std::cout << "Failed to initialize GLEW" << std::endl;
		return -1;
	}

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

	//ECS
		gCoordinator.Init();

		gCoordinator.RegisterComponent<Camera>();
		gCoordinator.RegisterComponent<Transform>();
		gCoordinator.RegisterComponent<Input>();

	//input system
		auto inputSystem = gCoordinator.RegisterSystem<MM::InputSystem>();
		Signature inputSiganture;
		inputSiganture.set(gCoordinator.GetComponentType<Input>());
		gCoordinator.SetSystemSignature<MM::InputSystem>(inputSiganture);

	//camera system
		auto cameraSystem = gCoordinator.RegisterSystem<MM::CameraSystem>();
		Signature camerasignature;
		camerasignature.set(gCoordinator.GetComponentType<Camera>());
		camerasignature.set(gCoordinator.GetComponentType<Transform>());
		gCoordinator.SetSystemSignature<MM::CameraSystem>(camerasignature);

		Entity camera = gCoordinator.CreateEntity();
		gCoordinator.AddComponent<Camera>(camera, Camera{
			65.0f,
			static_cast<float>(window.mWidth) / static_cast<float>(window.mHeight),
			0.1f,
			1000.0f
		});
		gCoordinator.AddComponent<Transform>(camera, Transform{
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(1.0f, 1.0f, 1.0f),
		});
		gCoordinator.AddComponent<Input>(camera, Input{});
		cameraSystem->SetCamera(camera);


		//where the entity is
		glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -10.0f));

		shader.setUniformi("u_texture", 0);

	MM::Renderer renderer;

	/* Loop until the user closes the window */
	while (!window.shouldWindowlose())
	{

		window.UpdateFrameRate();

		inputSystem->Update(window.mWindow);

		cameraSystem->MoveCamera();

		shader.setUniformMat4f("u_MVP", cameraSystem->GenerateProjectionMatrix() * cameraSystem->GetViewMatrix() * model);

		renderer.draw(vao, ibo, vbo, shader);

		/* Swap front and back buffers */
		window.SwapBuffers();

		/* Poll for and process events */
		window.PollEvents();
	}

	glfwTerminate();
	return 0;
}
