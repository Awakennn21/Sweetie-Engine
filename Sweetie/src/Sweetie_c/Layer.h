#pragma once

#include "Sweetie_c/Core.h"
#include "Sweetie_c/Events/Event.h"

namespace Sweetie
{
	class SW_API Layer
	{
	private:
		std::string m_DebugName;

	public:
		Layer(const std::string& name = "Layer")
			:m_DebugName(name) {}
		virtual ~Layer() {};

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& event) {}

		inline const std::string& GetName() const { return m_DebugName; }
	};
}

