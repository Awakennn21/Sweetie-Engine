#pragma once

#include "Sweetie_c/Window.h"
#include <GLFW/glfw3.h>

namespace Sweetie
{
	class WindowsWindow : public Window
	{
	private:
		GLFWwindow* m_Window;
		struct WindowData
		{
			std::string Title;
			unsigned int Height;
			unsigned int Width;
			bool VSync;

			EventCallbackFn EventCallback;
		} m_Data;


	public:




	private:


	public:
		WindowsWindow(const WindowProperties& Props);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		inline unsigned int GetWidth() const override { return m_Data.Width; }
		inline unsigned int GetHeight() const override { return m_Data.Height; }

		//Window Atributes
		inline void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;

		inline virtual void* GetNativeWindow() const override { return m_Window; };

	};
}