#include "pch.h"

#include "Application.h"
#include "Log.h"


#include "glad/glad.h"


namespace Sweetie
{
	Application* Application::s_AppInstance = nullptr;

	Sweetie::Application::Application()
	{
		SW_CORE_ASSERT(!s_AppInstance,"Application already exists")
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FUNCTION(Application::OnEvent));
		s_AppInstance = this;
		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		glCreateVertexArrays(1, &vao);
		glBindVertexArray(vao);

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

		VB.reset(VertexBuffer::Create(tab, sizeof(tab)));
		VB->Bind();
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, false, 2 * sizeof(float), 0);
		IB.reset(IndexBuffer::Create(Index, 3));
		S.reset(Shader::Create("../Sweetie/res/Shaders/BasicShaders.shader"));
		VB->Bind();
		IB->Bind();
		S->Bind();
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

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
			{
				layer->OnImGuiRender();
			}
			m_ImGuiLayer->End();
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
