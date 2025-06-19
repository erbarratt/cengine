#ifndef SHADER_HPP
#define SHADER_HPP
#include <string>

struct ShaderProgramSource
{
	std::string vertexSource;
	std::string fragmentSource;
};

namespace MarMyte {

class Shader {

public:
	explicit Shader(const char* filepath);
	void bind() const;
private:
	unsigned int program = 0;
	static ShaderProgramSource parseShader(const char* filepath);
	static unsigned int compileShader(unsigned int type, const std::string& source);
};

} // MarMyte

#endif //SHADER_HPP
