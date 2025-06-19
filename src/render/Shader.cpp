#include "Shader.hpp"

#include <filesystem>
#include <fstream>
#include <sstream>
#include <iostream>

#include "GLEW/glew.h"

namespace MarMyte {

	enum class ShaderType
	{
		NONE = -1,
		VERTEX = 0,
		FRAGMENT = 1,
	};

	/**
	 * Parse a combined shader source file into seperate shader type source strings ready to compile
	 * @param filepath path to combined shader program source file
	 * @return ShaderProgramSource
	 */
	ShaderProgramSource Shader::parseShader(const char* filepath)
	{

		std::ifstream stream(filepath);

		std::string line;
		std::stringstream ss[2];
		ShaderType type = ShaderType::NONE;
		while (std::getline(stream, line)) {
			if (line.find("#shader") != std::string::npos) {
				if (line.find("vertex") != std::string::npos) {
					type = ShaderType::VERTEX;
				} else if (line.find("fragment") != std::string::npos) {
					type = ShaderType::FRAGMENT;
				}
			} else {
				ss[(int)type] << line << std::endl;
			}
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

	/**
	 * Create a shader program from a combined shader source file
	 * @param filepath path to combined shader program source file
	 * @return unsigned int
	 */
	Shader::Shader(const char* filepath)
	{

		//convert file to src strings in a struct
		ShaderProgramSource src = parseShader(filepath);

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

	void Shader::bind() const
	{
		glUseProgram(program);
	}
} // MarMyte