#include "pch.h"
#include "Renderer.h"

void Sweetie::Renderer::BeginScene()
{
}

void Sweetie::Renderer::EndScene()
{
}

void Sweetie::Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray)
{
	RenderCommand::DrawIndexed(vertexArray);
}
