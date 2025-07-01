#include "Texture.hpp"
#include "../../external/stb_image.hpp"
#include <GLEW/glew.h>

namespace MM
{
	Texture::Texture(const std::string& path)
		:textureId(0), filepath(path), localBBuffer(nullptr), width(0), height(0), BPP(0)
	{

		// stbi_set_flip_vertically_on_load(true);
		localBBuffer = stbi_load(path.c_str(), &width, &height, &BPP, STBI_rgb_alpha);

		glGenTextures(1, &textureId);
		glBindTexture(GL_TEXTURE_2D, textureId);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, localBBuffer);
		glBindTexture(GL_TEXTURE_2D, 0);

		if (localBBuffer) {
			stbi_image_free(localBBuffer);
		}

	}

	Texture::~Texture()
	{
		//glDeleteTextures(1, &textureId);
	}

	void Texture::bind(unsigned int slot) const
	{
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, textureId);
	}

	void Texture::unbind() const
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}
