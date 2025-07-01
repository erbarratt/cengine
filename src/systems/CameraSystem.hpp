#ifndef CAMERASYSTEM_HPP
#define CAMERASYSTEM_HPP

#include "../core/System.hpp"
#include "GLM/glm.hpp"

namespace MM {

	class CameraSystem : public System
	{
		public:
			void SetCamera(Entity camera);
			void MoveCamera() const;
			void GenerateProjectionMatrix();
			[[nodiscard]] glm::mat4 GetViewMatrix() const;
			[[nodiscard]] glm::mat4 GetProjectionMatrix() const;
		private:
			Entity mCurrentCamera = 0;
			glm::mat4 mProjectionMatrix = {};
	};

} // MM

#endif //CAMERASYSTEM_HPP
