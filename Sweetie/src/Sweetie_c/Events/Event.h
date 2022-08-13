#pragma once

#include "../Core.h"
#include"../Log.h"


namespace Sweetie
{
	/*
	Events are currently blocking meaning that when an event occours
	the whole application stops to prosses that event
	TODO: redesign the system to hold events in some sort of a buffer
	and process all of them in order of occouring
	*/

	enum class ecEventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		KeyPressed, KeyReleased,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	enum eEventCategory
	{
		None = 0,
		EventCategoryApplication = BIT(0),
		EventCategoryInput       = BIT(1),
		EventCategoryKeyboard    = BIT(2),
		EventCategoryMouse		 = BIT(3),
		EventCategoryMouseButton = BIT(4)

	};

#define EVENT_CLASS_TYPE(type) static ecEventType GetStaticType() { return ecEventType::##type; }\
							   virtual ecEventType GetEventType() const override { return GetStaticType(); }\
							   virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategory() const override { return category; }

#define BIND_EVENT_FUNCTION(x) std::bind(&x, this, std::placeholders::_1)


	class SW_API Event
	{
		//fuction that communicates with an application 
		friend class EventDispatcher;

	public:
		bool m_Handeled = false;


	public:
		virtual ecEventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategory() const = 0;
		virtual std::string LogEvent() const { return GetName(); }

		inline bool IsInCategory(eEventCategory category)
		{
			return (GetCategory() & category);
		}

	};

	class SW_API EventDispatcher
	{
	private:
		template<typename T>
		using EventFunction = std::function<bool(T&)>;

		Event& m_Event;

	public:
		EventDispatcher(Event& event)
			: m_Event(event) {}

		template<typename T>
		bool Dispatch(EventFunction<T> Function)
		{
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				m_Event.m_Handeled = Function(*(T*)&m_Event);
				return true;
			}
			return false;
		}

	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.LogEvent();
	}


}