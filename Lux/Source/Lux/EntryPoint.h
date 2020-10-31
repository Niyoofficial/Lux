#pragma once

#ifdef LUX_PLATFORM_WINDOWS

extern Lux::Application* Lux::CreateApplication();

int main(int argc, char** argv)
{
	auto app = Lux::CreateApplication();
	app->Run();
	delete app;
}

#endif // LUX_PLATFORM_WINDOWS
