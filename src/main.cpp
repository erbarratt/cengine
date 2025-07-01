#include <chrono>
#include <iostream>
#include <sstream>
#include <GLEW/glew.h>

#include <GLM/glm.hpp>

#include "core/Window.hpp"
#include "core/Coordinator.hpp"
#include "core/Scene.hpp"

#include "components/Camera.hpp"
#include "components/Input.hpp"

#include "components/Transform.hpp"

#include "components/Mesh.hpp"
#include "components/Material.hpp"

#include "systems/InputSystem.hpp"
#include "systems/CameraSystem.hpp"
#include "systems/RenderableSystem.hpp"
#include "systems/RenderSystem.hpp"

Coordinator gCoordinator;
MM::Scene gScene;

int main()
{

	MM::Window window;
	if (!window.Init()) {
		return -1;
	}

	std::cout << glGetString(GL_VERSION) << std::endl;

	if (glewInit() != GLEW_OK) {
		std::cout << "Failed to initialize GLEW" << std::endl;
		return -1;
	}

	gCoordinator.Init();

	gCoordinator.RegisterComponent<Camera>();
	gCoordinator.RegisterComponent<Input>();

	gCoordinator.RegisterComponent<Transform>();

	gCoordinator.RegisterComponent<Mesh>();
	gCoordinator.RegisterComponent<Material>();

	//input system
		std::shared_ptr inputSystem = gCoordinator.RegisterSystem<MM::InputSystem>();
		Signature inputSiganture;
		inputSiganture.set(gCoordinator.GetComponentType<Input>());
		gCoordinator.SetSystemSignature<MM::InputSystem>(inputSiganture);

	//camera system
		std::shared_ptr cameraSystem = gCoordinator.RegisterSystem<MM::CameraSystem>();
		Signature camerasignature;
		camerasignature.set(gCoordinator.GetComponentType<Input>());
		camerasignature.set(gCoordinator.GetComponentType<Camera>());
		camerasignature.set(gCoordinator.GetComponentType<Transform>());
		gCoordinator.SetSystemSignature<MM::CameraSystem>(camerasignature);

	//renderable system
		std::shared_ptr renderableSystem = gCoordinator.RegisterSystem<MM::RenderableSystem>();
		Signature renderableSignature;
		renderableSignature.set(gCoordinator.GetComponentType<Mesh>());
		renderableSignature.set(gCoordinator.GetComponentType<Material>());
		gCoordinator.SetSystemSignature<MM::RenderableSystem>(renderableSignature);

	//render system
		std::shared_ptr renderSystem = gCoordinator.RegisterSystem<MM::RenderSystem>();
		Signature renderSignature;
		renderSignature.set(gCoordinator.GetComponentType<Mesh>());
		renderSignature.set(gCoordinator.GetComponentType<Material>());
		renderSignature.set(gCoordinator.GetComponentType<Transform>());
		gCoordinator.SetSystemSignature<MM::RenderSystem>(renderSignature);

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

	Entity plane = gCoordinator.CreateEntity();
	float positions[] = {
		-50.0f, 50.0f, 0.0f, 0.0f,
		50.0f, 50.0f, 1.0f, 0.0f,
		50.0f, -50.0f, 1.0f, 1.0f,
		-50.0f, -50.0f, 0.0f, 1.0f
	};
	unsigned int indices[] = {
		0,1,2,
		2,3,0
	};
	renderableSystem->SetMesh(plane, positions, indices);
	renderableSystem->SetMaterial(plane, "basic", "../../res/textures/checker-map_tho.png");
	gCoordinator.AddComponent<Transform>(plane, Transform{
		glm::vec3(0.0f, 0.0f, -10.0f),
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(1.0f, 1.0f, 1.0f),
	});

	while (!window.shouldWindowlose())
	{

		window.UpdateFrameRate();

		inputSystem->Update(window.mWindow);

		cameraSystem->MoveCamera();

		renderSystem->Render(cameraSystem->GetProjectionMatrix(), cameraSystem->GetViewMatrix());
		window.SwapBuffers();

		window.PollEvents();

	}

	glfwTerminate();
	return 0;
}
