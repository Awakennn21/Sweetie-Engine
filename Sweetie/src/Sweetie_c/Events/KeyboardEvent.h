#pragma once

#include "Event.h"

namespace Sweetie
{
	//All Keyboards share the same property -> keycode
	class SW_API KeyEvent : public Event
	{
	protected:
		int m_KeyCode;

	public:
		inline int GetKeyCode() const { return m_KeyCode; }

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)

	protected:
		KeyEvent(int KeyCode)
		{
			m_KeyCode = KeyCode;
		}
	
	};



	class SW_API EventKeyPressed : public KeyEvent
	{
	private:
		int m_KeyRepeatedCount;

	public:
		EventKeyPressed(int KeyCode, int KeyRepeatedCount)
			: KeyEvent(KeyCode)
		{
			m_KeyRepeatedCount = KeyRepeatedCount;
		}

		inline int GetKeyRepeatedCount() const { return m_KeyRepeatedCount; }

		std::string LogEvent() const override
		{
			std::stringstream ss;
			ss << "Key Pressed Event: " << m_KeyCode << " Repeated: " << m_KeyRepeatedCount << " times.";
			std::string str = ss.str();
			return str;
		}

		EVENT_CLASS_TYPE(KeyPressed);
	};



	class SW_API EventKeyReleased : public KeyEvent
	{
	private:
		int m_KeyRepeatedCount;

	public:
		EventKeyReleased(int KeyCode)
			: KeyEvent(KeyCode) {}

		inline int GetKeyRepeatedCount() const { return m_KeyRepeatedCount; }

		std::string LogEvent() const override
		{
			std::stringstream ss;
			ss << "Key Released Event: " << m_KeyCode;
			std::string str = ss.str();
			return str;
		}
		
		EVENT_CLASS_TYPE(KeyReleased);
	};
}