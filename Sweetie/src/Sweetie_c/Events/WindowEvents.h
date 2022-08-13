#pragma once 

#include "Event.h"

namespace Sweetie
{
	class SW_API EventWindowClose : public Event
	{
	public:
		EventWindowClose() {}

		std::string LogEvent() const override
		{
			std::stringstream ss;
			ss << "Window closed Event";
			std::string str = ss.str();
			return str;
		}

		EVENT_CLASS_TYPE(WindowClose);
		EVENT_CLASS_CATEGORY(EventCategoryApplication);

	};

	class SW_API EventWindowResize : public Event
	{
	private:
		unsigned int m_Width, m_Height;

	public:
		EventWindowResize(unsigned int Width, unsigned int Height)
			:m_Width(Width), m_Height(Height) {}

		inline unsigned int GetWidth() const { return m_Width; }
		inline unsigned int GetHeight() const { return m_Height; }

		std::string LogEvent() const override
		{
			std::stringstream ss;
			ss << "Window Resized to: " << m_Width << " " << m_Height;
			std::string str = ss.str();
			return str;
		}

		EVENT_CLASS_TYPE(WindowResize);
		EVENT_CLASS_CATEGORY(EventCategoryApplication);
	};
}