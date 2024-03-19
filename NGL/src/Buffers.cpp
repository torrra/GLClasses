#include "glad/glad.h"

#include "Buffers.h"

ngl::BufferObject::BufferObject()
{
	glCreateBuffers(1, &m_id);
}

ngl::BufferObject::BufferObject(unsigned long size, unsigned int* values, bool dynamic)
{
	glCreateBuffers(1, &m_id);

	if (dynamic)
		glNamedBufferData(m_id, size, values, GL_DYNAMIC_DRAW);
	else
		glNamedBufferData(m_id, size, values, GL_STATIC_DRAW);
}

ngl::BufferObject::BufferObject(unsigned long size, float* values, bool dynamic)
{
	glCreateBuffers(1, &m_id);

	if (dynamic)
		glNamedBufferData(m_id, size, values, GL_DYNAMIC_DRAW);
	else
		glNamedBufferData(m_id, size, values, GL_STATIC_DRAW);
}

void ngl::BufferObject::SetData(unsigned long size, unsigned int* values, bool dynamic) const
{
	if (dynamic)
		glNamedBufferData(m_id, size, values, GL_DYNAMIC_DRAW);
	else
		glNamedBufferData(m_id, size, values, GL_STATIC_DRAW);
}

void ngl::BufferObject::SetData(unsigned long size, float* values, bool dynamic) const
{
	if (dynamic)
		glNamedBufferData(m_id, size, values, GL_DYNAMIC_DRAW);
	else
		glNamedBufferData(m_id, size, values, GL_STATIC_DRAW);
}

void ngl::BufferObject::Delete()
{
	glDeleteBuffers(1, &m_id);
}

ngl::VertexArray::VertexArray()
{
	glCreateVertexArrays(1, &m_id);
}

void ngl::VertexArray::SetAttribute(unsigned int pos, int size, unsigned int offset, unsigned int vboID) const
{
	glEnableVertexArrayAttrib(m_id, pos);
	glVertexArrayAttribFormat(m_id, pos, size, GL_FLOAT, GL_FALSE, offset);
	glVertexArrayAttribBinding(m_id, pos, vboID);
}

void ngl::VertexArray::BindVBO(const BufferObject& vbo, unsigned int vboID, long long int offset, int stride) const
{
	glVertexArrayVertexBuffer(m_id, vboID, vbo.m_id, offset, stride);
}

void ngl::VertexArray::BindEBO(const BufferObject& ebo) const
{
	glVertexArrayElementBuffer(m_id, ebo.m_id);
}

void ngl::VertexArray::Draw(unsigned int mode, unsigned long num) const
{
	glBindVertexArray(m_id);
	glDrawElements(mode, num, GL_UNSIGNED_INT, 0);
}

void ngl::VertexArray::Delete()
{
	glDeleteVertexArrays(1, &m_id);
}
