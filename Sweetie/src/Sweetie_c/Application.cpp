#include "pch.h"

#include "Application.h"
#include "Log.h"

namespace Sweetie
{
	Application* Application::s_AppInstance = nullptr;

	Sweetie::Application::Application()
	{
		SW_CORE_ASSERT(!s_AppInstance, "Application already exists")
			m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FUNCTION(Application::OnEvent));
		s_AppInstance = this;
	}

	Sweetie::Application::~Application()
	{

	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher Dispacher(e);
		Dispacher.Dispatch<EventWindowClose>(BIND_EVENT_FUNCTION(Application::OnWindowClosed));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
		{
			if (e.m_Handeled)
			{
				break;
			}
			(*--it)->OnEvent(e);
		}
	}

	void Application::Run()
	{
		while (m_Running)
		{
			m_Window->OnUpdate();
			for (Layer* layer : m_LayerStack)
			{
				layer->OnUpdate();
			}
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);
	}

	bool Application::OnWindowClosed(EventWindowClose& e)
	{
		m_Running = false;
		return true;
	}
}
