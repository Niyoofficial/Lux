#include "Lux.h"

class Sandbox : public Lux::Application
{
public:
	Sandbox() {}
	~Sandbox() {}
};

Lux::Application* Lux::CreateApplication()
{
	return new Sandbox();
}
