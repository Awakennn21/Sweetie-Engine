#include "pch.h"
#include "RenderCommand.h"
#include "Platform/OpenGl/OpenGlRendererAPI.h"

namespace Sweetie
{
#ifdef OPENGL_RENDERING_API
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGlRendererAPI;
#else
	_Static_assert(false);
#endif // OPENGL_RENDERING_API
}