#pragma once

#include "Lux/Events/Event.h"

namespace Lux
{
	class LUX_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(float DeltaTime) {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& e) {}

		inline const std::string& GetName() const { return m_DebugName; } 
	protected:
		std::string m_DebugName;
	};
}
