#include "Sandbox2D.h"

#include <glad/glad.h>
#include <SDL3/SDL.h>
#include <glm/gtc/matrix_transform.hpp>

#include <memory>

class Sandbox : public Derelict::Application
{
public:
	Sandbox()
	{
		PushLayer(new Sandbox2D(m_Timer));

	}
	~Sandbox() {}

private:
};

Derelict::Application* Derelict::CreateApplication()
{
	return new Sandbox();
}