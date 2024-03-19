#pragma once

namespace ngl
{
	class Sampler
	{
	public:
		Sampler();

		void SetParameter(unsigned int param, int value);
		void SetParameter(unsigned int param, float value);

		unsigned int m_id = 999;
	};


	class Texture
	{
	public:
		Texture() = delete;
		Texture(const char* filePath);
		Texture(const unsigned char* pixels, int height, int width);

		void SetParameter(unsigned int param, unsigned int value) const;
		void SetParameter(unsigned int param, float value) const;

		void BindToUnit(unsigned int textureUnit, const Sampler& sampler) const;

		~Texture() = default;

		unsigned int m_id = 999;
	};


}