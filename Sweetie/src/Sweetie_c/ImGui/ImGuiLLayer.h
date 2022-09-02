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

	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;
		void Begin();
		void End();
	};
}

