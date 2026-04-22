#include "Sandbox2D.h"

#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Platform/OpenGL/OpenGLShader.h"

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.f / 720.f)
{
}

void Sandbox2D::OnAttach()
{
	
}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(Lily::Timestep ts)
{
	// Update
	//LL_TRACE("Delta time: {0}s {1}ms", ts.GetSeconds(), ts.GetMilliSeconds());

	m_CameraController.OnUpdate(ts);

	// Render
	Lily::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	Lily::RenderCommand::Clear();

	Lily::Renderer2D::BeginScene(m_CameraController.GetCamera());

	Lily::Renderer2D::DrawQuad({ 0.f, 0.f }, { 1.f, 1.f }, { 0.8f, 0.2f, 0.3f, 1.f });

	Lily::Renderer2D::EndScene();

	/*
	std::dynamic_pointer_cast<Lily::OpenGLShader>(m_FlatColorShader)->Bind();
	std::dynamic_pointer_cast<Lily::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat4("u_Color", m_SquareColor);
	
	Lily::Renderer::Submit(m_FlatColorShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
	*/
	
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void Sandbox2D::OnEvent(Lily::Event& e)
{
	m_CameraController.OnEvent(e);
}
