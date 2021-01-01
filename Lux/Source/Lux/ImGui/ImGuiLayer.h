#pragma once

#include "Lux/Layer.h"
#include "Lux/Events/MouseEvent.h"
#include "Lux/Events/KeyEvent.h"
#include "Lux/Events/ApplicationEvent.h"

namespace Lux
{
	class LUX_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();
	private:
		float m_Time = 0.f;
	};
}