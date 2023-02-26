#include "pch.h"
#include "OpenGlRendererAPI.h"
#include <glad/glad.h>

namespace Sweetie
{
	void OpenGlRendererAPI::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGlRendererAPI::Clear(glm::vec4 Color)
	{
		glClearColor(Color.r,Color.g,Color.b,Color.a);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void OpenGlRendererAPI::DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
	{
		vertexArray->Bind();
		glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
	}

	void OpenGlRendererAPI::EnableCulling()
	{
		glEnable(GL_CULL_FACE);
	}

	void OpenGlRendererAPI::DisableCulling()
	{
		glDisable(GL_CULL_FACE);
	}

}
