#ifndef RENDERER_HPP
#define RENDERER_HPP
#include <string>

struct ShaderProgramSource
{
	std::string vertexSource;
	std::string fragmentSource;
};

namespace MarMyte {

class Shaders {

public:
	static unsigned int createShaderProgram(const char* filepath);
private:
	static ShaderProgramSource parseShader(const char* filepath);
	static unsigned int compileShader(unsigned int type, const std::string& source);
};

} // MarMyte

#endif //RENDERER_HPP
