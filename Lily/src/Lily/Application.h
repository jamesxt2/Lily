#pragma once

#include "Core.h"
#include "Events/Event.h"

namespace Lily {

	class LILY_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	// To be defined in client
	Application* CreateApplication();
}