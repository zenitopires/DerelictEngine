#pragma once

#include "../Renderer/OrthographicCamera.h"
#include "../Events/ApplicationEvent.h"
#include "../Events/MouseEvent.h"

#include <glm/glm.hpp>

#include <functional>

namespace Derelict {
#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

	class OrthographicCameraController
	{
	public:
		OrthographicCameraController(float aspectRatio, bool rotation = false); // aspect ration * 2 units

		void OnUpdate(float deltaTime);
		void OnEvent(Event& e);

	private:
		bool OnMouseScrolled(MouseScrollEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);

	private:
		float m_ZoomLevel = 1.0f;
		float m_AspectRatio;

		OrthographicCamera m_Camera;

		bool m_Rotation;
		glm::vec3 m_CameraPosition;
	};
}