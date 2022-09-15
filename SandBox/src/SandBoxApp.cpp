#pragma once
#include <Sweetie.h>

class RenderLayer : public Sweetie::Layer
{
	Sweetie::OpenGLRenderer Renderer;
	float tab[6] =
	{
		-0.1f,-0.5f,
		0.8f,0.3f,
		0.9f,0.2f
	};
	void OnUpdate()
	{
		Renderer.Clear();
		Renderer.RenderShape(Sweetie::RendererShapes::RS_Triangle, tab, 0.4f, 0.0f, 0.0f);
	}
	void OnEvent(Sweetie::Event& e)
	{
		Sweetie::EventDispatcher d(e);
		d.Dispatch<Sweetie::EventMouseMoved>(BIND_EVENT_FUNCTION(RenderLayer::OnMouseMoved));
		d.Dispatch<Sweetie::EventKeyPressed>(BIND_EVENT_FUNCTION(RenderLayer::OnKeyPressed));
	}
	bool OnMouseMoved(Sweetie::EventMouseMoved& e)
	{
		SW_INFO("{0}", e.GetMouseY());
		tab[4] = ((float)(e.GetMouseX()) / (1920.f / 2.f)) - 1.0f;
		tab[5] = (((float)(e.GetMouseY()) / (1080.f / 2.f)) - 1.0f) * -1.f;
		return true;
	}
	bool OnKeyPressed(Sweetie::EventKeyPressed& e)
	{
		if (e.GetKeyCode() != SW_KEY_J)
		{
			SW_TRACE("{0}", (char)e.GetKeyCode());
		}
		return true;
	}
};

class  Sandbox : public Sweetie::Application
{

public:
	Sandbox()
	{
		PushLayer(new RenderLayer);
	}
	~Sandbox()
	{

	}
};

Sweetie::Application* Sweetie::CreateApplication()
{
	return new Sandbox;
}
