#pragma once
#include "Platform/Rendering/RendererAPI.h"

namespace Sweetie
{
	class RenderCommand
	{
	private:
		static RendererAPI* s_RendererAPI;
	public:
		inline static void Clear()
		{
			s_RendererAPI->Clear();
		}

		inline static void Clear(glm::vec4 Color)
		{
			s_RendererAPI->Clear(Color);
		}

		inline static void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
		{
			s_RendererAPI->DrawIndexed(vertexArray);
		}
	};
}