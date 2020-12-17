#include "Lux.h"
#include "Lux/Layer.h"
#include "Lux/Events/Event.h"
#include "Lux/Input.h"
#include "Lux/KeyCodes.h"

class ExampleLayer : public Lux::Layer
{
public:
	ExampleLayer()
		:Layer("Example") {}

	void OnUpdate() override
	{
	}

	void OnEvent(Lux::Event& e) override
	{
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
