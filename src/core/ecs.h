#pragma once
#include <bitset>

#include "GLM/glm.hpp"
#include <GLM/gtc/quaternion.hpp>

// Used to define the size of arrays later on
constexpr unsigned int MAX_ENTITIES = 5000;
constexpr unsigned char MAX_COMPONENTS = 32;

/*
 * An Entity Signature is a 32-bit "bit set"
 * This means each entity can have a max of 32 Components...
 */
using Signature = std::bitset<MAX_COMPONENTS>;

struct Transform
{
	glm::vec4 position;
	glm::quat rotation;
	glm::vec3 scale;
};