#include "Lux.h"
#include "Lux/Layer.h"
#include "Lux/Events/Event.h"
#include "Lux/Input.h"

class ExampleLayer : public Lux::Layer
{
public:
	ExampleLayer()
		:Layer("Example") {}

	void OnUpdate() override
	{
		//LX_INFO("Update");
		LX_TRACE("{0}, {1}", Lux::Input::GetMousePosition().first, Lux::Input::GetMousePosition().second);
	}

	void OnEvent(Lux::Event& e) override
	{
		//LX_INFO(e);
	}
};

class Sandbox : public Lux::Application
{
public:
	Sandbox() 
	{
		PushLayer(new ExampleLayer());
		PushLayer(new Lux::ImGuiLayer());
	}
	~Sandbox() {}
};

Lux::Application* Lux::CreateApplication()
{
	return new Sandbox();
}
