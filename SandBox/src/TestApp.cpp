//#pragma once
//#include <Sweetie.h>
//#include <Windows.h>
//#include "../../Sweetie/src/Platform/Rendering/Buffers.h"
//#include "../../Sweetie/src/Platform/Rendering/Shader.h"
//#include "../../Sweetie/src/Platform/Rendering/VertexArray.h"
//#include "../../Sweetie/src/Platform/OpenGl/OpenGlBuffers.cpp"
//#include "../../Sweetie/src/Platform/Rendering/Renderer.h"
//
//using namespace Sweetie;
//class RenderLayer : public Sweetie::Layer
//{
//	float tab[12] =
//	{
//		0.0f, 0.7f, 0.0f, 8.4f,
//		-0.7f,-0.7f, 0.0f, 5.f,
//		0.7f,-0.7f, 0+.0f, 9.3f
//	};
//	uint32_t Index[3] =
//	{
//		0,1,2
//	};
//	std::shared_ptr<VertexArray> VAO;
//	std::shared_ptr<VertexBuffer> VB;
//	std::shared_ptr<IndexBuffer> IB;
//	std::shared_ptr<Shader> S;
//	
//
//public:
//	RenderLayer()
//	{
//		VAO.reset(VertexArray::Create());
//		VAO->Bind();
//
//		VB.reset(VertexBuffer::Create(tab, sizeof(tab)));
//		VB->Bind();
//		BufferLayout Layout =
//		{
//			{BufferElementType::Float3,"Positon"},
//			{BufferElementType::Float,"Random"}
//		}; 
//		VB->SetLayout(Layout);	
//		VAO->AddVertexBuffer(VB);
//		
//
//		IB.reset(IndexBuffer::Create(Index, 3));
//		IB->Bind();
//		VAO->SetIndexBuffer(IB);
//
//
//		S.reset(Shader::Create("../Sweetie/res/Shaders/BasicShaders.shader"));
//		S->Bind();
//	}
//
//	void OnUpdate()
//	{
//		RenderCommand::Clear({ 0.8f,0.8f,0.8f,0.8f });
//
//
//		Renderer::BeginScene();
//		{
//			S->Bind();
//			Renderer::Submit(VAO);
//		}
//		Renderer::EndScene();
//
//	}
//	void OnEvent(Sweetie::Event& e)
//	{
//		Sweetie::EventDispatcher d(e);
//		d.Dispatch<Sweetie::EventMouseMoved>(BIND_EVENT_FUNCTION(RenderLayer::OnMouseMoved));
//		d.Dispatch<Sweetie::EventMouseButtonPressed>(BIND_EVENT_FUNCTION(RenderLayer::OnMouseButtonPressed));
//	}
//	bool OnMouseMoved(Sweetie::EventMouseMoved& e)
//	{
//		return true;
//	}
//	bool OnMouseButtonPressed(Sweetie::EventMouseButtonPressed& e)
//	{
//		WindowsInput i;
//		if (e.GetButtonCode() == SW_MOUSE_BUTTON_LEFT)
//		{
//			POINT p;
//			GetCursorPos(&p);
//			SW_INFO("{0} , {1}", p.x, p.y);
//		}
//		return true;
//	}
//};
//
//class  Test : public Sweetie::Application
//{
//
//public:
//	Test()
//		:Application()
//	{
//		PushLayer(new RenderLayer());
//	}
//};
//
//Sweetie::Application* Sweetie::CreateApplication()
//{
//	return new Test;
//}
