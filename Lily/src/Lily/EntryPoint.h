#pragma once

#ifdef LL_PLATFORM_WINDOWS

extern Lily::Application* Lily::CreateApplication();

void main(int argc, char** argv)
{
	printf("Lily Engine\n");
	auto app = Lily::CreateApplication();
	app->Run();
	delete app;
}

#endif