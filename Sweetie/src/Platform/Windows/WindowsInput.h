#pragma once
#include "Sweetie_c/Input.h"
namespace Sweetie
{
	class WindowsInput : public Input
	{
	protected:
		virtual bool IsKeyPressedImplementation(int keycode) override;
		virtual bool IsMouseButtonPressedImplementation(int button) override;
		virtual float GetMouseXImplementation() override;
		virtual float GetMouseYImplementation() override;
	};
}

