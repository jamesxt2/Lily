#pragma once

#include "Core.h"

#include "LayerStack.h"
#include "Events/Event.h"
#include "Window.h"
#include "Events/ApplicationEvent.h"

#include "Lily/ImGui/ImGuiLayer.h"

#include "Lily/Renderer/Shader.h"
#include "Lily/Renderer/Buffer.h"
#include "Lily/Renderer/VertexArray.h"

#include "Lily/Renderer/OrthographicCamera.h"

namespace Lily {

	class LILY_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;

		static Application* s_Instance;
	};

	// To be defined in client
	Application* CreateApplication();
}