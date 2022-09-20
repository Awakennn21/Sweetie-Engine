#pragma once
#include "pch.h"
#include "Platform/Rendering/Buffers.h"

namespace Sweetie
{

	class OpenGlVertexArray
	{
	private:
		uint32_t m_VertexArrayId;
		std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffers;
		std::shared_ptr<IndexBuffer> m_IndexBuffer;
	public:
		OpenGlVertexArray();
		~OpenGlVertexArray();

		void AddVertexBuffer(std::shared_ptr<VertexBuffer> buffer);
		void SetIndexBuffer(std::shared_ptr<IndexBuffer> buffer);

		void Bind() const;
		void UnBind() const;

		static OpenGlVertexArray* Create() { return new OpenGlVertexArray; };
	};

}