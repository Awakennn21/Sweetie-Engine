#pragma once
#include "pch.h"
namespace Sweetie
{
	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() {}

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		static VertexBuffer* Create(float* Vertecies, uint32_t size);
	};

	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() {}

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;
		virtual uint32_t GetCount() const = 0;
		static IndexBuffer* Create(uint32_t* Indices, uint32_t count);
	};
}
