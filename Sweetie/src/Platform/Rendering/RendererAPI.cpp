#include "pch.h"
#include "RendererAPI.h"

namespace Sweetie
{
#ifdef OPENGL_RENDERING_API
	RendererAPI::API RendererAPI::sm_API = RendererAPI::API::OpenGL;
#else
	_Static_assert(false);
	return nullptr;
#endif // OPENGL_RENDERING_API
}