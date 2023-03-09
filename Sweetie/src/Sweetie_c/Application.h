#pragma once
#include "Core.h"
#include "Events/Event.h"
#include "Events/WindowEvents.h"
#include "Events/MouseEvent.h"
#include "Events/KeyboardEvent.h"
#include "Sweetie_c/Window.h"
#include "Sweetie_c/LayerStack.h"
#include "Input.h"

namespace Sweetie
{
	class SW_API Application
	{
	private:
		static Application* s_AppInstance;

		std::unique_ptr<Window> m_Window;
		LayerStack m_LayerStack;
		bool m_Running;
	public:

	private:
		bool OnWindowClosed(EventWindowClose& e);

	public:
		inline Window& GetWindow() { return *m_Window; }
		static inline Application& Get() { return *s_AppInstance; }

		Application();
		virtual ~Application();
		void OnEvent(Event& e);

		void Run();
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

	};

	//To be defined in client
	Application* CreateApplication();
}

