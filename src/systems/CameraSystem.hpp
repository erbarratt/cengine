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
			glm::mat4 GetProjectionMatrix();
			glm::mat4 GetViewMatrix() const;
		private:
			Entity mCurrentCamera = 0;
	};

} // MM

#endif //CAMERASYSTEM_HPP
