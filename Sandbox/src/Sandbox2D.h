#pragma once

#include "Lily.h"

class Sandbox2D : public Lily::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	virtual void OnUpdate(Lily::Timestep ts) override;
	virtual void OnImGuiRender() override;
	virtual void OnEvent(Lily::Event& e) override;

private:
	Lily::OrthographicCameraController m_CameraController;

	// temp
	Lily::Ref<Lily::VertexArray> m_SquareVA;
	Lily::Ref<Lily::Shader> m_FlatColorShader;

	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.f };
};