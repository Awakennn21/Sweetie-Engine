#include "pch.h"
#include "OpenGlBuffers.h"
#include "Sweetie_c/Log.h"
#include <glad/glad.h>
	
namespace Sweetie
{
	static GLenum BufferElementTypeToOpenGLType(BufferElementType type)
	{
		switch (type)
		{
		case Sweetie::BufferElementType::None:		return GL_FLOAT;
		case Sweetie::BufferElementType::Float:		return GL_FLOAT;
		case Sweetie::BufferElementType::Float2:	return GL_FLOAT;
		case Sweetie::BufferElementType::Float3:	return GL_FLOAT;
		case Sweetie::BufferElementType::Float4:	return GL_FLOAT;
		case Sweetie::BufferElementType::Int:		return GL_INT;
		case Sweetie::BufferElementType::Int2:		return GL_INT;
		case Sweetie::BufferElementType::Int3:		return GL_INT;
		case Sweetie::BufferElementType::Int4:		return GL_INT;
		case Sweetie::BufferElementType::Mat3:		return GL_FLOAT;
		case Sweetie::BufferElementType::Mat4:		return GL_FLOAT;
		case Sweetie::BufferElementType::Bool:		return GL_BOOL;
		}
	}

	OpenGlVertexBuffer::OpenGlVertexBuffer(float* Vertecies, uint32_t size)
	{
		glCreateBuffers(1, &BufferId);
		glBindBuffer(GL_ARRAY_BUFFER, BufferId);
		glBufferData(GL_ARRAY_BUFFER, size, Vertecies, GL_STATIC_DRAW);
	}

	OpenGlVertexBuffer::~OpenGlVertexBuffer()
	{
		glDeleteBuffers(1, &BufferId);
	}

	void OpenGlVertexBuffer::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, BufferId);
	}

	void OpenGlVertexBuffer::UnBind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	OpenGlIndexBuffer::OpenGlIndexBuffer(uint32_t* Indecies, uint32_t count)
		:m_IndicesCount(count)
	{
		glCreateBuffers(1, &BufferId);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, BufferId);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), Indecies, GL_STATIC_DRAW);
	}

	OpenGlIndexBuffer::~OpenGlIndexBuffer()
	{
		glDeleteBuffers(1, &BufferId);
	}

	void OpenGlIndexBuffer::Bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, BufferId);
	}

	void OpenGlIndexBuffer::UnBind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}

