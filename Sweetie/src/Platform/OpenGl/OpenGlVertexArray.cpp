#include "pch.h"
#include "OpenGlVertexArray.h"
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

	OpenGlVertexArray::OpenGlVertexArray()
	{
		glCreateVertexArrays(1, &m_VertexArrayId);
		glBindVertexArray(m_VertexArrayId);
	}

	OpenGlVertexArray::~OpenGlVertexArray()
	{

	}

	void OpenGlVertexArray::AddVertexBuffer(std::shared_ptr<VertexBuffer> buffer)
	{
		glBindVertexArray(m_VertexArrayId);
		buffer->Bind();

		const auto& layout = buffer->GetLayout();
		uint32_t index = 0;
		for (const auto& element : layout)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer
			(
				index,
				element.GetComponentCount(),
				BufferElementTypeToOpenGLType(element.m_Type),
				element.mb_ToNormalize ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(const void*)element.m_Offset
			);
			index++;
		}
		m_VertexBuffers.push_back(buffer);
	}

	void OpenGlVertexArray::SetIndexBuffer(std::shared_ptr<IndexBuffer> buffer)
	{
		glBindVertexArray(m_VertexArrayId);
		m_IndexBuffer = buffer;
	}

	void OpenGlVertexArray::Bind() const
	{
		glBindVertexArray(m_VertexArrayId);

	}

	void OpenGlVertexArray::UnBind() const
	{
		glBindVertexArray(0);
	}
}
