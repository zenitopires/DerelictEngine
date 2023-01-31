#include "Derelict/src/Derelict/Core/Application.h"

extern Derelict::Application* CreateApplication();

int main()
{

	auto app = Derelict::CreateApplication();
	app->Run();
	delete app;
	return 0;

}