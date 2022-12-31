#include "WindowsWindow.h"

#include <iostream>

namespace Derelict
{
	static bool s_SDLInitialized = false;

	Window* Window::Create(const WindowProps& props /* = WindowProps() */)
	{
		return new WindowsWindow(props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		Init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}

	void WindowsWindow::OnUpdate()
	{

	}

	void WindowsWindow::Init(const WindowProps& props)
	{
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		if (!s_SDLInitialized)
		{
			int success = SDL_Init(SDL_INIT_VIDEO);
			
			if (success < 0) 
			{
				std::cout << "Failed to start SDL\n" << SDL_GetError() << '\n';
				exit(1);
			}

			s_SDLInitialized = true;
		}
		SDL_GL_LoadLibrary(NULL);
		SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

		m_Window = SDL_CreateWindow(props.Title.c_str(),
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			props.Width, props.Height, 
			// This should depend upon the renderer's configurations
			SDL_WINDOW_OPENGL);

		if (m_Window == nullptr)
		{
			std::cout << "Failed to create SDL window\n";
			SDL_Quit();
		}

		std::cout << "Successful window creation.\n";
	}

	void WindowsWindow::Shutdown()
	{
		SDL_DestroyWindow(m_Window);
		SDL_Quit();
	}

}