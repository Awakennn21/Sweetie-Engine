#include "pch.h"
#include "Buffers.h"
#include "Platform/OpenGl/OpenGlBuffers.h"

namespace Sweetie
{
	VertexBuffer* VertexBuffer::Create(float* Vertecies, uint32_t size)
	{
		return new OpenGlVertexBuffer(Vertecies, size);
	}


	IndexBuffer* IndexBuffer::Create(uint32_t* Indices, uint32_t count)
	{
		return new OpenGlIndexBuffer(Indices, count);
	}
}