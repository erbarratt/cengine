#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#pragma once

#include "../render/Shader.hpp"
#include "../render/Texture.hpp"

struct Material
{
	MM::Shader shader;
	MM::Texture texture;
};

#endif //MATERIAL_HPP
