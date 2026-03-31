#include "Application.h"

#include "Lily/Events/ApplicationEvent.h"
#include "Lily/Log.h"

namespace Lily {

	Application::Application()
	{
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		WindowResizeEvent e(1280, 720);
		//LL_TRACE(e);

		while (true);
	}

}