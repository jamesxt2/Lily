#pragma once

#ifdef LL_PLATFORM_WINDOWS

extern Lily::Application* Lily::CreateApplication();

void main(int argc, char** argv)
{
	Lily::Log::Init();
	LL_CORE_WARN("Init!");

	auto app = Lily::CreateApplication();
	app->Run();
	delete app;
}

#endif