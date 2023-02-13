#include "OrthographicCameraController.h"

#include "Input.h"
#include <SDL3/SDL.h>

namespace Derelict {

	OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation)
		: m_AspectRatio(aspectRatio), m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel), m_Rotation(rotation)
	{

	}

	void OrthographicCameraController::OnUpdate(float deltaTime)
	{
		if (Input::IsKeyPressed(SDL_SCANCODE_A))
		{
			m_CameraPosition.x -= 1.0f * deltaTime;
		}
		else if (Input::IsKeyPressed(SDL_SCANCODE_D))
		{
			m_CameraPosition.x += 1.0f * deltaTime;
		}
		if (Input::IsKeyPressed(SDL_SCANCODE_S))
		{
			m_CameraPosition.y -= 1.0f * deltaTime;
		}
		else if (Input::IsKeyPressed(SDL_SCANCODE_W))
		{
			m_CameraPosition.y += 1.0f * deltaTime;
		}

		m_Camera.SetPosition(m_CameraPosition);

	}

	void OrthographicCameraController::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrollEvent>(BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
	}

	bool OrthographicCameraController::OnMouseScrolled(MouseScrollEvent& e)
	{
		m_ZoomLevel -= e.GetYOffset();
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}

	bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& e)
	{
		m_AspectRatio -= (float)e.GetWidth() / (float)e.GetHeight();
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}

}