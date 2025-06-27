#pragma once
#include "../Component.hpp"

namespace MarMyte
{

	class Mesh : Component
	{
	public:
		explicit Mesh(const bool enable) : Component(ComponentType::MESH, enable){}

		void update() override;
		void fixedUpdate() override;
	};
}
