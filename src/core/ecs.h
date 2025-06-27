#pragma once
#include <bitset>

#include "GLM/glm.hpp"

//alias's
using Entity = unsigned int;
using ComponentType = unsigned char;

// Used to define the size of arrays later on
constexpr Entity MAX_ENTITIES = 5000;
constexpr ComponentType MAX_COMPONENTS = 32;

using Signature = std::bitset<MAX_COMPONENTS>;

struct Transform
{
	glm::vec4 position;
	glm::quat rotation;
	glm::vec3 scale;
};