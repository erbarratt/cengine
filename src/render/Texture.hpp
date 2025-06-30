#pragma once
#include <string>
#include <GLEW/glew.h>

#ifndef TEXTURE_HPP
#define TEXTURE_HPP

namespace MM
{
	class Texture {
	private:
		unsigned int textureId{};
		std::string filepath;
		unsigned char* localBBuffer;
		int width, height, BPP{};
	public:
		Texture(const std::string& path);
		~Texture();

		void bind(unsigned int slot = 0) const;
		void unbind() const;

		inline unsigned int getWidth() const { return width; }
		inline unsigned int getHeight() const { return height; }
	};
}

#endif //TEXTURE_HPP
