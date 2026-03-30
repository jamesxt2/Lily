#include "Lily.h"

class Sandbox : public Lily::Application
{
public:
	Sandbox()
	{

	}

	~Sandbox()
	{

	}
};

Lily::Application* Lily::CreateApplication()
{
	return new Sandbox();
}