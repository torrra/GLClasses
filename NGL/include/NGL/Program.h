#pragma once

#include <vector>

namespace ngl
{

	class Shader
	{
	public:
		Shader() = delete;
		Shader(const char* source, unsigned int shaderType);

		~Shader() = default;

		void Compile() const;

		void Delete() const;

		const char*		m_source = nullptr;
		unsigned int	m_type = 999;
		unsigned int	m_id = 999;
	};

	class Program
	{
	public:

		Program();

		void AddShader(Shader& shader);
		void ReadShaderSource(const char* shaderSource, unsigned int shaderType);
		void ImportShader(const char* sourcePath, unsigned int shaderType);

		void Link() const;
		void Use() const;
		void Delete();

		void SetUniform(const char* name, int value);
		void SetUniform(const char* name, float value);

		std::vector<Shader>		m_shaders;
		unsigned int			m_id = 999;
	};

}