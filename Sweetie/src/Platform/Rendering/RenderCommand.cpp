#include "pch.h"
#include "RenderCommand.h"
#include "Platform/OpenGl/OpenGlRendererAPI.h"

namespace Sweetie
{
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGlRendererAPI;
}