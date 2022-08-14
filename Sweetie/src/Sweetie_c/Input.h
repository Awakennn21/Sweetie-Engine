#pragma once
#include "Sweetie_c/Core.h"

namespace Sweetie
{
	class SW_API Input
	{
	private:
		static Input* s_Instance;
	public:
		inline static bool IsKEyPressed(int keycode) { return s_Instance->IsKeyPressedImplementation(keycode); }

		inline static bool IsMouseButtonPressed(int button) { return s_Instance->IsMouseButtonPressedImplementation(button); }
		inline static float GetMouseX() { return s_Instance->GetMouseXImplementation(); }
		inline static float GetMouseY() { return s_Instance->GetMouseYImplementation(); }

	protected:
		virtual bool IsKeyPressedImplementation(int keycode) = 0;
		virtual bool IsMouseButtonPressedImplementation(int button) = 0;
		virtual float GetMouseXImplementation() = 0;
		virtual float GetMouseYImplementation() = 0;
		
	};
}

