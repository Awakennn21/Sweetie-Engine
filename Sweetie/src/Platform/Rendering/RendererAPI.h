#pragma once
#include "pch.h"
#include "Platform/Rendering/VertexArray.h"
#include "Platform/Rendering/Shader.h"
#include "Platform/Rendering/Camera.h"
#include <glm/glm.hpp>

namespace Sweetie
{
	class RendererAPI
	{
	public:
		enum class API
		{
			None = 0, OpenGL = 1
		};
	private:
		static API sm_API;
	public:
		inline static API GetAPI() { return sm_API; }

		virtual void Clear() = 0;
		virtual void Clear(glm::vec4 Color) = 0;
		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) = 0;
		virtual void EnableCulling() = 0;
		virtual void DisableCulling() = 0;

	};

}

