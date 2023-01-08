#pragma once

#include "../Events/Event.h"

#include <string>
#include <functional>

namespace Derelict {
	struct WindowProps
	{
		std::string Title;
		unsigned int Width;
		unsigned int Height;
		bool Vsync;

		WindowProps(std::string_view title = "Derelict Engine",
			unsigned int width = 1280, unsigned int height = 720, bool vsync = false)
			: Title(title), Width(width), Height(height), Vsync(vsync)
		{}
	};

	class Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() {}

		virtual void OnUpdate() = 0;
		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;
		virtual void SetVsync(bool vsync) = 0;

		virtual void* GetNativeWindow() const = 0;
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;

		static Window* Create(const WindowProps& props = WindowProps());
	};
}