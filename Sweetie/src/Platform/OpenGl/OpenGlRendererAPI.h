#pragma once
#include "Platform/Rendering/RendererAPI.h"
#include <glm/glm.hpp>

namespace Sweetie
{
	class OpenGlRendererAPI : public RendererAPI
	{
	public:
		virtual void Clear() override;
		virtual void Clear(glm::vec4 Color) override;
		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray);
		virtual void EnableCulling() override;
		virtual void DisableCulling() override;

	};
}

