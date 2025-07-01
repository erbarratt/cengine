#pragma once
#include <string>
#include <GLEW/glew.h>

#ifndef TEXTURE_HPP
#define TEXTURE_HPP

namespace MM
{
	class Texture {
	private:

		std::string filepath;
		unsigned char* localBBuffer;
		int width, height, BPP{};
	public:
		unsigned int textureId;
		Texture(const std::string& path);
		~Texture();

		void bind(unsigned int slot = 0) const;
		void unbind() const;

		[[nodiscard]] inline unsigned int getWidth() const { return width; }
		[[nodiscard]] inline unsigned int getHeight() const { return height; }
	};
}

#endif //TEXTURE_HPP
