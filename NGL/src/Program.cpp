#include <iostream>
#include <fstream>

#include <filesystem>

#include "glad/glad.h"

#include "Program.h"

namespace ngl
{

	Shader::Shader(const char* source, unsigned int shaderType)
		: m_source(source), m_type(shaderType)
	{

		m_id = glCreateShader(m_type);

		Compile();
	}

	void Shader::Compile() const
	{
		int success;

		glShaderSource(m_id, 1, &m_source, NULL);
		glCompileShader(m_id);
		glGetShaderiv(m_id, GL_COMPILE_STATUS, &success);

		if (!success)
		{
			char infoLog[512];

			glGetShaderInfoLog(m_id, 512, NULL, infoLog);

			if (m_type == GL_FRAGMENT_SHADER)
				std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;

			else if (m_type == GL_VERTEX_SHADER)
				std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;

		}
	}

	void Shader::Delete() const
	{
		glDeleteShader(m_id);
	}

	Program::Program()
	{
		m_id = glCreateProgram();
	}

	void Program::AddShader(Shader& shader)
	{
		m_shaders.push_back(shader);
	}

	void Program::ReadShaderSource(const char* shaderSource, unsigned int shaderType)
	{
		m_shaders.emplace_back(shaderSource, shaderType);
	}

	void Program::ImportShader(const char* sourcePath, unsigned int shaderType)
	{
		// Equivalent to fopen(filename, "rb")
		std::ifstream  sourceFile(sourcePath, std::ios::in | std::ios::binary);

		// TODO: Debug remove
		std::cout << std::filesystem::current_path().string() << std::endl;

		if (sourceFile)
		{
			char* sourceCode;

			sourceFile.seekg(0, std::ios::end);

			unsigned int length = static_cast<unsigned int>(sourceFile.tellg());

			sourceCode = new char[length + 1];

			sourceFile.seekg(std::ios::beg);

			sourceFile.read(sourceCode, length);

			sourceCode[length] = '\0';

			sourceFile.close();

			ReadShaderSource(sourceCode, shaderType);

			delete[] sourceCode;
		}
		else
			std::cout << "ERROR::SHADER::CANNOT_OPEN_FILE\n" << sourcePath << std::endl;


	}

	void Program::Link() const
	{
		for (const Shader& shader : m_shaders)
		{
			glAttachShader(m_id, shader.m_id);
		}

		int success;

		glLinkProgram(m_id);

		glGetProgramiv(m_id, GL_LINK_STATUS, &success);

		if (!success)
		{
			char infoLog[512];

			glGetProgramInfoLog(m_id, 512, NULL, infoLog);

			std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		}
	}

	void Program::Use() const
	{
		glUseProgram(m_id);
	}

	void Program::Delete()
	{
		for (const Shader& shader : m_shaders)
			glDeleteShader(shader.m_id);

		glDeleteProgram(m_id);

		m_shaders.clear();

	}

	void Program::SetUniform(const char* name, int value)
	{
		glUniform1i(glGetUniformLocation(m_id, name), value);
	}

	void Program::SetUniform(const char* name, float value)
	{
		glUniform1f(glGetUniformLocation(m_id, name), value);
	}

}
