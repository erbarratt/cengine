#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#pragma once

#include "../render/Shader.hpp"
#include "../render/Texture.hpp"

struct Material
{
	unsigned int shaderProgram;
	unsigned int textureId;
};

#endif //MATERIAL_HPP
