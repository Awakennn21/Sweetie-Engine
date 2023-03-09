#pragma once

#include "pch.h"

#include "Sweetie_c/Core/Core.h"
#include "Sweetie_c/Events/Event.h"

namespace Sweetie
{
	struct WindowProperties
	{
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		WindowProperties(const std::string& title = "Sweetie Engine",
			unsigned int width = 1920,
			unsigned int height = 1080)
			: Title(title), Width(width), Height(height) {}
	};

	//Interface representing desktop system based Window
	class SW_API Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window()
		{

		}

		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		//Window Atributes
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		virtual void* GetNativeWindow() const = 0;

		static Window* Create(const WindowProperties& props = WindowProperties());


	};
}