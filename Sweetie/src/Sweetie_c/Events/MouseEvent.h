#pragma once

#include "Event.h"

namespace Sweetie
{
	class SW_API EventMouseMoved : public Event
	{
	protected:
		float m_MouseX, m_MouseY;

	public:
		inline int GetMouseX() const { return m_MouseX; }
		inline int GetMouseY() const { return m_MouseY; }
		
		std::string LogEvent() const override
		{
			std::stringstream ss;
			ss << "Mouse Moved Event(X,Y): "<< m_MouseX<<"," << m_MouseY;
			std::string str = ss.str();
			return str;
		}

		EVENT_CLASS_TYPE(MouseMoved);
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput);

	public:
		EventMouseMoved(int X, int Y)
			:m_MouseX(X), m_MouseY(Y) {}

	};



	class SW_API EventMouseScrolled : public Event
	{
	private:
		float m_XOffset, m_YOffset;

	public:
		EventMouseScrolled(float XOffset, float YOffset)
			:m_XOffset(XOffset), m_YOffset(YOffset) {}
		
		inline float GetXOffset() const { return m_XOffset; }
		inline float GetYOffset() const { return m_YOffset; }
		
		std::string LogEvent() const override
		{
			std::stringstream ss;
			ss << "Mouse Scrolled Event(X,Y): " << m_XOffset << "," << m_YOffset;
			std::string str = ss.str();
			return str;
		}

		EVENT_CLASS_TYPE(MouseScrolled);
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput);

	};



	class SW_API EventMouseButton : public Event
	{
	protected:
		int m_ButtonCode;

	public:
		inline int GetButtonCode() const { return m_ButtonCode; }

		EVENT_CLASS_CATEGORY(EventCategoryMouseButton | EventCategoryInput);

	protected:
		EventMouseButton(int ButtonCode)
			: m_ButtonCode(ButtonCode) {}
	};



	class SW_API EventMouseButtonPressed : public EventMouseButton
	{
	public:
		EventMouseButtonPressed(int ButtonCode)
			:EventMouseButton(ButtonCode) {}

		std::string LogEvent() const override
		{
			std::stringstream ss;
			ss << "Mouse Button Pressed Event: "<< m_ButtonCode;
			std::string str = ss.str();
			return str;
		}

		EVENT_CLASS_TYPE(MouseButtonPressed);
	};



	class SW_API EventMouseButtonReleased : public EventMouseButton
	{
	public:
		EventMouseButtonReleased(int ButtonCode)
			:EventMouseButton(ButtonCode) {}

		std::string LogEvent() const override
		{
			std::stringstream ss;
			ss << "Mouse Button Released Event: "<< m_ButtonCode;
			std::string str = ss.str();
			return str;
		}

		EVENT_CLASS_TYPE(MouseButtonReleased);
	};
}