#include "CameraSystem.hpp"

#include "../core/Coordinator.hpp"
#include "../components/Camera.hpp"
#include "../components/Transform.hpp"
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>

extern Coordinator gCoordinator;

namespace MM {

	void CameraSystem::SetCamera(const Entity camera)
	{
		mCurrentCamera = camera;
	}

	// void CameraSystem::MoveCamera() const
	// {
	// 	//process inputs
	// 	auto& transform = gCoordinator.GetComponent<Transform>(mCurrentCamera);
	// 	transform.position.x += 1.0f;
	// }

	glm::mat4 CameraSystem::GetProjectionMatrix()
	{
		auto& cameraSettings = gCoordinator.GetComponent<Camera>(mCurrentCamera);
		return glm::perspective(glm::radians(cameraSettings.fov), cameraSettings.aspectRatio, cameraSettings.nearPlane, cameraSettings.farPlane);
	}

	glm::mat4 CameraSystem::GetViewMatrix() const
	{

		auto& transform = gCoordinator.GetComponent<Transform>(mCurrentCamera);

		//first create a rotation matrix around the Y axis
		glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::radians(transform.rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));

		//then create a translation matrix
		glm::mat4 translate = glm::translate(glm::mat4(1.0f), transform.position);

		//combine these for the resulting matrix
		return rotation * translate;

	}
} // MM