#pragma once
#include "Events/EventQueue.h"
#include "LayerStack.h"

namespace Sweetie
{
	class EventHandler
	{
	private:
		std::shared_ptr<EventQueue> m_EventQueue;
		std::shared_ptr<LayerStack> m_LayerStack;
		bool m_RunningApp;

	public:
		EventHandler(std::shared_ptr<LayerStack> layerStack)
		{
			m_EventQueue = std::make_shared<EventQueue>();
			m_LayerStack = layerStack;
			m_RunningApp = true;
		}

		void SetEventHandlerState(bool shouldRun) { m_RunningApp = shouldRun; }

		void Run()
		{
			while(m_RunningApp)
			{
				if (m_EventQueue->GetSize() > 0)
				{
					Event& e = m_EventQueue->HandleNext();
					for (auto it = m_LayerStack->end(); it != m_LayerStack->begin(); )
					{
						if (e.m_Handeled)
						{
							break;
						}
						(*--it)->OnEvent(e);
					}
				}
			}
		}

		inline std::shared_ptr<EventQueue> GetEventQueue() const { return m_EventQueue; }
	};
}
