#pragma once

#include "../Events/Event.h"

#include <string>

namespace Derelict {
	class Layer
	{
	public:
		Layer(std::string_view name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnEvent(Event& event) {}

		inline std::string_view GetName() { return m_DebugName; }

	protected:
		std::string m_DebugName;
		bool m_Enabled = false;

	};
}

