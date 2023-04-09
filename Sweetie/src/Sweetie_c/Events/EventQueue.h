#pragma once
#include "pch.h"
#include "Event.h"

namespace Sweetie
{
	class EventQueue
	{
	private:
		std::list<Event*> m_EventQueue;
		std::atomic<unsigned int> m_EventsPending;
		std::mutex m_Lock;

	public:
		EventQueue()
			:m_EventsPending(0) {}

		inline uint32_t GetSize() const { return m_EventsPending; }

		void PushEvent(Event& e)
		{
			std::lock_guard<std::mutex> LockGuard(m_Lock);
			m_EventQueue.push_back(&e);
			m_EventsPending++;
		}

		Event& HandleNext()
		{
			std::lock_guard<std::mutex> LockGuard(m_Lock);
			Event& e = *m_EventQueue.front();
			m_EventQueue.pop_front();
			m_EventsPending--;
			return e;
		}
	};
}