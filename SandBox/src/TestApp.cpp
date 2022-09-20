#pragma once
#include <Sweetie.h>

#include "../../Sweetie/src/Platform/Rendering/Buffers.h"
#include "../../Sweetie/src/Platform/Rendering/Shader.h"
#include "../../Sweetie/src/Platform/OpenGl/OpenGlVertexArray.h"
#include "../../Sweetie/src/Platform/OpenGl/OpenGlBuffers.cpp"
#include <glad/glad.h>

using namespace Sweetie;
class RenderLayer : public Sweetie::Layer
{
	float tab[9] =
	{
		-0.5f,-0.5f, 0.00f,
		0.0f,0.5f, 0.0f,
		0.5f,-0.5f, 0.00f
	};
	uint32_t Index[3] =
	{
		0,1,2
	};
	std::shared_ptr<OpenGlVertexArray> VAO;
	std::shared_ptr<VertexBuffer> VB;
	std::shared_ptr<IndexBuffer> IB;
	std::shared_ptr<Shader> S;
	unsigned int vao;


public:
	RenderLayer()
	{
		VAO.reset(OpenGlVertexArray::Create());
		VAO->Bind();


		VB.reset(VertexBuffer::Create(tab, sizeof(tab)));
		VB->Bind();
		BufferLayout Layout =
		{
			{BufferElementType::Float3,"Positon"}
		}; 
		VB->SetLayout(Layout);	
		VAO->AddVertexBuffer(VB);
		

		IB.reset(IndexBuffer::Create(Index, 3));
		IB->Bind();
		VAO->SetIndexBuffer(IB);


		S.reset(Shader::Create("../Sweetie/res/Shaders/BasicShaders.shader"));
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
