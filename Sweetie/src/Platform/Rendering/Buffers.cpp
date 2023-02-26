#include "pch.h"
#include "Buffers.h"
#include "Platform/OpenGl/OpenGlBuffers.h"

namespace Sweetie
{
	VertexBuffer* VertexBuffer::Create(float* Vertecies, uint32_t size)
	{
#ifdef OPENGL_RENDERING_API
		return new OpenGlVertexBuffer(Vertecies, size);
#else
		_Static_assert(false);
		return nullptr;
#endif // OPENGL_RENDERING_API
	}


	IndexBuffer* IndexBuffer::Create(uint32_t* Indices, uint32_t count)
	{
#ifdef OPENGL_RENDERING_API
		return new OpenGlIndexBuffer(Indices, count);
#else
		_Static_assert(false);
		return nullptr;
#endif // OPENGL_RENDERING_API

	}
}