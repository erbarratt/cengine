#ifndef SHADER_HPP
#define SHADER_HPP
#include <string>
#include <unordered_map>

#include "GLM/fwd.hpp"

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

		void setUniform1f(const std::string &name, float value);

		void setUniform4f(const std::string &name, float v0, float v1, float v2, float v3);
		void setUniformMat4f(const std::string &name, const glm::mat4 &matrix);

	private:
		unsigned int program = 0;
		std::unordered_map<std::string, int> uniformLocationCache;
		static ShaderProgramSource parseShader(const char* filepath);
		static unsigned int compileShader(unsigned int type, const std::string& source);
		int GetUniformLocation(const std::string& name);
	};

} // MarMyte

#endif //SHADER_HPP
