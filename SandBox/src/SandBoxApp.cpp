#pragma once
#include <Sweetie.h>

#include "../../Sweetie/src/Platform/Rendering/Buffers.h"
#include "../../Sweetie/src/Platform/Rendering/Shader.h"
#include "../../Sweetie/src/Platform/OpenGl/OpenGlBuffers.cpp"
#include <glad/glad.h>

using namespace Sweetie;
class RenderLayer : public Sweetie::Layer
{
	float tab[6] =
	{
		-0.5f,-0.5f,
		-0.5f,0.5f,
		0.5f,-0.5f
	};
	uint32_t Index[3] =
	{
		0,1,2
	};
	std::unique_ptr<VertexBuffer> VB;
	std::unique_ptr<IndexBuffer> IB;
	std::unique_ptr<Shader> S;
	unsigned int vao;


public:
	RenderLayer()
	{
		glCreateVertexArrays(1, &vao);
		glBindVertexArray(vao);
		VB.reset(VertexBuffer::Create(tab, sizeof(tab)));
		VB->Bind();
		BufferLayout Layout =
		{
			{BufferElementType::Float2,"Positon"}
		};

		uint32_t index = 0;
		for (const auto& element : Layout)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer
			(
				index,
				element.GetComponentCount(),
				BufferElementTypeToOpenGLType(element.m_Type),
				element.mb_ToNormalize ? GL_TRUE : GL_FALSE,
				Layout.GetStride(),
				(const void*)element.m_Offset
			);
			index++;
		}
		IB.reset(IndexBuffer::Create(Index, 3));
		S.reset(Shader::Create("../Sweetie/res/Shaders/BasicShaders.shader"));
		VB->Bind();
		IB->Bind();
		S->Bind();
	}

	void OnUpdate()
	{
		glClearColor(0.9f, 0.9f, 0.9f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);
	}
	void OnEvent(Sweetie::Event& e)
	{
		Sweetie::EventDispatcher d(e);
		d.Dispatch<Sweetie::EventMouseMoved>(BIND_EVENT_FUNCTION(RenderLayer::OnMouseMoved));
		d.Dispatch<Sweetie::EventKeyPressed>(BIND_EVENT_FUNCTION(RenderLayer::OnKeyPressed));
	}
	bool OnMouseMoved(Sweetie::EventMouseMoved& e)
	{
		return true;
	}
	bool OnKeyPressed(Sweetie::EventKeyPressed& e)
	{
		return true;
	}
};

class  Test : public Sweetie::Application
{

public:
	Test()
		:Application()
	{
		PushLayer(new RenderLayer());
	}
};

Sweetie::Application* Sweetie::CreateApplication()
{
	return new Test;
}
