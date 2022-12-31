#include "Derelict/src/Derelict/Core/Application.h"

class Sandbox : public Derelict::Application
{
public:
	Sandbox() = default;
	~Sandbox() {}
};

Derelict::Application* Derelict::CreateApplication()
{
	return new Sandbox();
}