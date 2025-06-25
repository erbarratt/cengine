#ifndef SHADER_HPP
#define SHADER_HPP
#include <string>
#include <unordered_map>

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
	void setUniformi(const std::string& name, int value);

private:
	unsigned int program = 0;
	std::unordered_map<std::string, int> uniformLocationCache;
	static ShaderProgramSource parseShader(const char* filepath);
	static unsigned int compileShader(unsigned int type, const std::string& source);
	int GetUniformLocation(const std::string& name);
};

} // MarMyte

#endif //SHADER_HPP
