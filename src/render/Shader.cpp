#include "Shader.hpp"

#include <filesystem>
#include <fstream>
#include <sstream>
#include <iostream>

#include "GLDebug.h"
#include "GLEW/glew.h"
#include "GLM/glm.hpp"

namespace MarMyte {

	enum class ShaderType
	{
		NONE = -1,
		VERTEX = 0,
		FRAGMENT = 1,
	};

	/**
	 * Create a shader program from a combined shader source file
	 * @param name path to combined shader program source file
	 * @return unsigned int
	 */
		Shader::Shader(const char* name)
		{

			//parse the shaders of this name
			ShaderProgramSource src = parseShader(name);

			//create an id ref to an empty shaeder program object
			const unsigned int prog = glCreateProgram();

			//compile the shader src and return an id to that compiled shader
			const unsigned int vs = compileShader(GL_VERTEX_SHADER, src.vertexSource);
			const unsigned int fs = compileShader(GL_FRAGMENT_SHADER, src.fragmentSource);

			//attach the compiled shader to the empty program
			glAttachShader(prog, vs);
			glAttachShader(prog, fs);

			//link and validate the shader program
			glLinkProgram(prog);
			glValidateProgram(prog);

			//now the shaders are in the program and the program is linked, cleanup the shaders.
			glDeleteShader(vs);
			glDeleteShader(fs);

			program = prog;
		}

	/**
	 * Parse a combined shader source file into seperate shader type source strings ready to compile
	 * @param name path to combined shader program source file
	 * @return ShaderProgramSource
	 */
		ShaderProgramSource Shader::parseShader(const char* name)
		{

			std::ifstream streamVert("../../res/shaders/" + std::string(name) + ".vert");

			std::string line;
			std::stringstream ss[2];

			while (std::getline(streamVert, line)) {
				ss[0] << line << std::endl;
			}

			std::ifstream streamFrag("../../res/shaders/" + std::string(name) + ".frag");

			while (std::getline(streamFrag, line)) {
				ss[1] << line << std::endl;
			}

			return {ss[0].str(), ss[1].str()};

		}

	/**
	 * Generate a shader object and compile its source into it
	 * @param type The type of shader being compiled
	 * @param source The source for that shader type
	 * @return unsigned int
	 */
		unsigned int Shader::compileShader(const unsigned int type, const std::string &source)
		{

			//generate an empty shader object and get it's id
			const unsigned int id = glCreateShader(type);

			//set and compile the source for that shader
			const char* src = source.c_str();
			glShaderSource(id, 1, &src, nullptr);
			glCompileShader(id);

			//check it's ok!
			int result;
			glGetShaderiv(id, GL_COMPILE_STATUS, &result);
			if (result == GL_FALSE) {
				int length;
				glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
				char* message = (char*)alloca(length);
				glGetShaderInfoLog(id, length, &length, message);
				std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertext" : "fragment") << " shader!" << std::endl;
				std::cout << message << std::endl;
				glDeleteShader(id);
				return 0;
			}

			return id;
		}

		void Shader::setUniformi(const std::string &name, const int value)
		{
			glUniform1i(GetUniformLocation(name), value);
		}

		void Shader::setUniform1f(const std::string &name, const float value)
		{
			glUniform1f(GetUniformLocation(name), value);
		}

		void Shader::setUniform4f(const std::string &name, const float v0, const float v1, const float v2, const float v3)
		{
			glUniform4f(GetUniformLocation(name), v0, v1, v2, v3);
		}

		void Shader::setUniformMat4f(const std::string &name, const glm::mat4& matrix)
		{
			CGL(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));
		}

		int Shader::GetUniformLocation(const std::string &name)
		{
			if (uniformLocationCache.find(name) != uniformLocationCache.end()) {
				return uniformLocationCache[name];
			}

			const int location = glGetUniformLocation(program, name.c_str());
			if (location == -1) {
				std::cout << "Failed to get uniform location " << name << std::endl;
			}

			uniformLocationCache[name] = location;
			return location;
		}

	void Shader::bind() const
	{
		glUseProgram(program);
	}
} // MarMyte