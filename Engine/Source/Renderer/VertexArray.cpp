#include "VertexArray.h"

#include "glad/glad.h"

Quiet::VertexArray::VertexArray()
{
	glGenVertexArrays(1, &m_RendererID);
	glBindVertexArray(m_RendererID);
}

Quiet::VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_RendererID);
}

void Quiet::VertexArray::Bind() const
{
	glBindVertexArray(m_RendererID);
}

void Quiet::VertexArray::Unbind() const
{
	glBindVertexArray(0);
}
