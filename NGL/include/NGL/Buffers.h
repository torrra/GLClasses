#pragma once

namespace ngl
{
	class BufferObject
	{
	public:

		BufferObject();

		BufferObject(unsigned long size, unsigned int* values, bool dynamic = false);
		BufferObject(unsigned long size, float* values, bool dynamic = false);


		void SetData(unsigned long size, unsigned int* values, bool dynamic = false) const;
		void SetData(unsigned long size, float* values, bool dynamic = false) const;

		void Delete();

		unsigned int m_id;
	};


	class VertexArray
	{
	public:
		VertexArray();

		void SetAttribute(unsigned int pos, int size, unsigned int offset, unsigned int vboID) const;

		void BindVBO(const BufferObject& vbo, unsigned int vboID, long long int offset, int stride) const;
		void BindEBO(const BufferObject& ebo) const;

		void Draw(unsigned int mode, unsigned long num) const;

		void Delete();

		unsigned int m_id;
	};

	using EBO = BufferObject;
	using VBO = BufferObject;
	using VAO = VertexArray;

}