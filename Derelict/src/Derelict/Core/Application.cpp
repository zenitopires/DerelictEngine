#include <SDL3/SDL.h>
#include <iostream>
#include <glad/glad.h>

#include "../Events/ApplicationEvent.h"

//int main()
//{
//	//int windowFlags, rendererFlags;
//
//	//windowFlags = SDL_WINDOW_OPENGL;
//	//rendererFlags = SDL_RENDERER_ACCELERATED;
//
//	//if (SDL_Init(SDL_INIT_VIDEO) < 0) {
//	//	std::cout << "Failed to start SDL\n" << SDL_GetError() << '\n';
//	//	exit(1);
//	//}
//
//	//SDL_GL_LoadLibrary(NULL);
//	//SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
//	//SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
//	//SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
//	//SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
//	//SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
//
//
//	//SDL_Window* window = SDL_CreateWindow("Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
//	//	1280, 720, windowFlags);
//
//	//auto context = SDL_GL_CreateContext(window);
//
//	//gladLoadGLLoader(SDL_GL_GetProcAddress);
//
//	////SDL_Renderer* renderer = SDL_CreateRenderer(window, nullptr, rendererFlags);
//
//	////if (renderer == nullptr) {
//	////	std::cout << "Could not create renderer! " << SDL_GetError() << '\n';
//	////}
//
//	//SDL_Event event;
//
//	//printf("OpenGL loaded\n");
//	//gladLoadGLLoader(SDL_GL_GetProcAddress);
//	//printf("Vendor:   %s\n", glGetString(GL_VENDOR));
//	//printf("Renderer: %s\n", glGetString(GL_RENDERER));
//	//printf("Version:  %s\n", glGetString(GL_VERSION));
//
//	//while (true)
//	//{
//	//	while (SDL_PollEvent(&event))
//	//	{
//	//		switch (event.type)
//	//		{
//	//		case SDL_QUIT:
//	//			std::cout << "QUIT\n";
//	//			break;
//	//		case SDL_KEYDOWN:
//	//			std::cout << "Keydown\n";
//	//			break;
//	//		case SDL_KEYUP:
//	//			std::cout << "Keyup\n";
//	//			break;
//	//		}
//	//	}
//	//}
//
//	return 0;
//}

#include "Application.h"

namespace Derelict {
#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		if (s_Instance) 
		{
			std::cout << "Instance of application already exists.\n";
			exit(-1);
		}

		s_Instance = this;
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Input = std::unique_ptr<Input>(Input::Create());
		m_Input->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		while (m_Running)
		{
			glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			m_Input->OnUpdate();

			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	void Application::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);

		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));
	}

	//Derelict::Application* Application::s_Instance;

}