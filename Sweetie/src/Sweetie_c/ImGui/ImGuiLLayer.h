#pragma once
#include "Sweetie_c/Core.h"
#include "Sweetie_c/Layer.h"

#include "Sweetie_c/Events/KeyboardEvent.h"
#include "Sweetie_c/Events/WindowEvents.h"
#include "Sweetie_c/Events/MouseEvent.h"

namespace Sweetie
{
	class SW_API ImGuiLayer : public Layer
	{
	private:
		float m_Time;

	private:
		bool OnMouseButtonPressed(EventMouseButtonPressed& e);
		bool OnMouseButtonReleased(EventMouseButtonReleased& e);
		bool OnMouseMoved(EventMouseMoved& e);
		bool OnMouseScrolled(EventMouseScrolled& e);
		bool OnKeyPressed(EventKeyPressed& e);
		bool OnKeyReleased(EventKeyReleased& e);
		bool OnWindowResize(EventWindowResize& e);

		static int ImGui_ImplGlfw_KeyToImGuiKey(int key);
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach();
		void OnDetach();
		void OnUpdate();
		void OnEvent(Event& event);
	};
}

