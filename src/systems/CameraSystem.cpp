#include "CameraSystem.hpp"

#include "../core/Coordinator.hpp"
#include "../components/Camera.hpp"
#include "../components/Transform.hpp"
#include "../components/Input.hpp"
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>

extern Coordinator gCoordinator;

namespace MM {

	void CameraSystem::SetCamera(const Entity camera)
	{
		mCurrentCamera = camera;
		GenerateProjectionMatrix();
	}

	void CameraSystem::MoveCamera() const
	{
		//process inputs
		auto& input = gCoordinator.GetComponent<Input>(mCurrentCamera);
		auto& transform = gCoordinator.GetComponent<Transform>(mCurrentCamera);

		if (input.up) {
			transform.position.y --;
		} else if (input.down) {
			transform.position.y ++;
		}

		if (input.a) {
			transform.position.x ++;
		} else if (input.d) {
			transform.position.x --;
		}

		if (input.w) {
			transform.position.z ++;
		} else if (input.s) {
			transform.position.z --;
		}

		if (input.left) {
			transform.rotation.y --;
		} else if (input.right) {
			transform.rotation.y ++;
		}

	}

	void CameraSystem::GenerateProjectionMatrix()
	{
		auto& cameraSettings = gCoordinator.GetComponent<Camera>(mCurrentCamera);
		mProjectionMatrix = glm::perspective(glm::radians(cameraSettings.fov), cameraSettings.aspectRatio, cameraSettings.nearPlane, cameraSettings.farPlane);
	}

	glm::mat4 CameraSystem::GetViewMatrix() const
	{

		const auto& transform = gCoordinator.GetComponent<Transform>(mCurrentCamera);

		//first create a rotation matrix around the Y axis
		const glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::radians(transform.rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));

		//then create a translation matrix
		const glm::mat4 translate = glm::translate(glm::mat4(1.0f), transform.position);

		//combine these for the resulting matrix
		return rotation * translate;

	}

	glm::mat4 CameraSystem::GetProjectionMatrix() const
	{
		return mProjectionMatrix;
	}
} // MM