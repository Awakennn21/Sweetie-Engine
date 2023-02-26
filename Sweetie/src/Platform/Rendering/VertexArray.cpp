#include "pch.h"
#include "VertexArray.h"
#include "Platform/OpenGl/OpenGlVertexArray.h"

namespace Sweetie
{
	VertexArray* VertexArray::Create()
	{
#ifdef OPENGL_RENDERING_API
		return new OpenGlVertexArray();
#else
		_Static_assert(false);
		return nullptr;
#endif // OPENGL_RENDERING_API
	}
}
