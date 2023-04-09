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
		m_LayerStack = std::make_shared<LayerStack>();
		m_Window->SetEventCallback(BIND_EVENT_FUNCTION(Application::OnEvent));
		m_EventHandler = std::shared_ptr<EventHandler>(new EventHandler(m_LayerStack));
		m_EventHandlingThread = std::thread(&EventHandler::Run, m_EventHandler);
		s_AppInstance = this;
	}

	Sweetie::Application::~Application()
	{
		m_EventHandler->SetEventHandlerState(false);
		m_EventHandlingThread.join();
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher Dispacher(e);
		Dispacher.Dispatch<EventWindowClose>(BIND_EVENT_FUNCTION(Application::OnWindowClosed));
		m_EventHandler->GetEventQueue()->PushEvent(e);
		SW_TRACE("{0}", m_EventHandler->GetEventQueue()->GetSize());
	}

	void Application::Run()
	{	
		while (m_Running)
		{
			m_Window->OnUpdate();
			for (auto it : *m_LayerStack)
			{
				it->OnUpdate();
			}
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack->PushLayer(layer);
	}

	void Application::PushOverlay(Layer* overlay)
	{
		m_LayerStack->PushOverlay(overlay);
	}

	bool Application::OnWindowClosed(EventWindowClose& e)
	{
		m_Running = false;
		return true;
	}
}
