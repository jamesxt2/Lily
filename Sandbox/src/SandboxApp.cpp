#include "Lily.h"

#include "imgui/imgui.h"

class ExampleLayer : public Lily::Layer 
{
public:
	ExampleLayer()
		: Layer("Example")
	{
	}

	void OnUpdate() override
	{
		if (Lily::Input::IsKeyPressed(LL_KEY_TAB))
			LL_TRACE("TAB!!!");
	}

	void OnEvent(Lily::Event& event) override
	{
		if (event.GetEventType() == Lily::EventType::KeyPressed)
		{
			Lily::KeyPressedEvent& e = (Lily::KeyPressedEvent&)event;
			LL_TRACE("{0}", (char)e.GetKeyCode());
		}
	}

	void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		ImGui::Text("Hello World");
		ImGui::End();
	}
};

class Sandbox : public Lily::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}
};

Lily::Application* Lily::CreateApplication()
{
	return new Sandbox();
}