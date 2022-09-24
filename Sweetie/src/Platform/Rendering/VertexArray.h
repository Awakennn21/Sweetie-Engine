#pragma once
#include "pch.h"
#include "Platform/Rendering/Buffers.h"

namespace Sweetie
{

	class VertexArray
	{
	public:
		
		virtual ~VertexArray() {};

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		virtual void AddVertexBuffer(std::shared_ptr<VertexBuffer> buffer) = 0;
		virtual void SetIndexBuffer(std::shared_ptr<IndexBuffer> buffer) = 0;
		virtual std::vector<std::shared_ptr<VertexBuffer>> GetVertexBuffers() = 0;
		virtual std::shared_ptr<IndexBuffer> GetIndexBuffer() = 0;

		static VertexArray* Create();
	};

}