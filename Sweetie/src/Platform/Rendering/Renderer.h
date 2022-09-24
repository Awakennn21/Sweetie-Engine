#pragma once
#include "RenderCommand.h"

namespace Sweetie
{
	class Renderer
	{
	public:
		inline static RendererAPI::API GetApi() { return RendererAPI::GetAPI(); }

		static void BeginScene();
		static void EndScene();

		static void Submit(const std::shared_ptr<VertexArray>& vertexArray);

	};
}