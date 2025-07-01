#include <chrono>
#include <iostream>
#include <sstream>
#include <GLEW/glew.h>

#include <GLM/glm.hpp>

#include "core/Window.hpp"

#include "components/Camera.hpp"
#include "components/Input.hpp"

#include "components/Transform.hpp"

#include "components/Mesh.hpp"
#include "components/Material.hpp"

#include "core/Coordinator.hpp"

#include "systems/CameraSystem.hpp"
#include "systems/InputSystem.hpp"
#include "systems/RenderableSystem.hpp"
#include "systems/RenderSystem.hpp"

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

	//ECS
		gCoordinator.Init();

		gCoordinator.RegisterComponent<Camera>();
		gCoordinator.RegisterComponent<Input>();

		gCoordinator.RegisterComponent<Transform>();

		gCoordinator.RegisterComponent<Mesh>();
		// gCoordinator.RegisterComponent<Material>();


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

	//renderable system
		// auto renderableSystem = gCoordinator.RegisterSystem<MM::RenderableSystem>();
		// Signature renderableSignature;
		// renderableSignature.set(gCoordinator.GetComponentType<Mesh>());
		// renderableSignature.set(gCoordinator.GetComponentType<Material>());
		// gCoordinator.SetSystemSignature<MM::RenderableSystem>(renderableSignature);
		//
		// Entity plane = gCoordinator.CreateEntity();
		// const float positions[] = {
		// 	-50.0f, 50.0f, 0.0f, 0.0f,
		// 	50.0f, 50.0f, 1.0f, 0.0f,
		// 	50.0f, -50.0f, 1.0f, 1.0f,
		// 	-50.0f, -50.0f, 0.0f, 1.0f
		// };
		// const unsigned int indices[] = {
		// 	0,1,2,
		// 	2,3,0
		// };
		// renderableSystem->SetMesh(plane, positions, indices);
		// renderableSystem->SetMaterial(plane, "basic", "../../res/textures/checker-map_tho.png");
		// gCoordinator.AddComponent<Transform>(plane, Transform{
		// 	glm::vec3(0.0f, 0.0f, -10.0f),
		// 	glm::vec3(0.0f, 0.0f, 0.0f),
		// 	glm::vec3(1.0f, 1.0f, 1.0f),
		// });

	//render system
		// auto rendererSystem = gCoordinator.RegisterSystem<MM::RenderSystem>();
		// Signature renderSignature;
		// camerasignature.set(gCoordinator.GetComponentType<Camera>());
		// camerasignature.set(gCoordinator.GetComponentType<Transform>());
		// renderSignature.set(gCoordinator.GetComponentType<Mesh>());
		// renderSignature.set(gCoordinator.GetComponentType<Material>());
		// gCoordinator.SetSystemSignature<MM::RenderableSystem>(renderSignature);

	/* Loop until the user closes the window */
	while (!window.shouldWindowlose())
	{

		window.UpdateFrameRate();

		inputSystem->Update(window.mWindow);

		cameraSystem->MoveCamera();

		//rendererSystem->Render(cameraSystem->GetProjectionMatrix(), cameraSystem->GetViewMatrix());
		window.SwapBuffers();

		/* Poll for and process events */
		window.PollEvents();
	}

	glfwTerminate();
	return 0;
}
