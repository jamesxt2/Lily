#include "Lily.h"
#include "Lily/Core/EntryPoint.h"

#include "Platform/OpenGL/OpenGLShader.h"

#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Sandbox2D.h"

class ExampleLayer : public Lily::Layer 
{
public:
	ExampleLayer()
		: Layer("Example"), m_CameraController(1280.f / 720.f, true)
	{
		m_VertexArray = Lily::VertexArray::Create();

		float vertices[] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			0.0f, 0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		Lily::Ref<Lily::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Lily::VertexBuffer::Create(vertices, sizeof(vertices)));

		Lily::BufferLayout layout = {
			{ Lily::ShaderDataType::Float3, "a_Position" },
			{ Lily::ShaderDataType::Float4, "a_Color" }
		};
		vertexBuffer->SetLayout(layout);

		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		Lily::Ref<Lily::IndexBuffer> indexBuffer;
		indexBuffer.reset(Lily::IndexBuffer::Create(indices, 3));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA = Lily::VertexArray::Create();

		float squareVertices[] = {
			-0.5f, -0.5f, 0.0f, 0.f, 0.f,
			0.5f, -0.5f, 0.0f, 1.f, 0.f,
			0.5f, 0.5f, 0.0f, 1.f, 1.f,
			-0.5f, 0.5f, 0.0f, 0.f, 1.f
		};

		Lily::Ref<Lily::VertexBuffer> squareVB;
		squareVB.reset(Lily::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

		squareVB->SetLayout({
			{ Lily::ShaderDataType::Float3, "a_Position" },
			{ Lily::ShaderDataType::Float2, "a_TexCoord" }
			});

		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		Lily::Ref<Lily::IndexBuffer> squareIB;
		squareIB.reset(Lily::IndexBuffer::Create(squareIndices, 6));
		m_SquareVA->SetIndexBuffer(squareIB);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;
			
			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";  // location = 0 means at index 0, a means attribute

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			
			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";

		m_Shader = Lily::Shader::Create("VertexPosColor", vertexSrc, fragmentSrc);

		std::string flatColorShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;
			
			void main()
			{
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";  // location = 0 means at index 0, a means attribute

		std::string flatColorShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			uniform vec3 u_Color;

			void main()
			{
				color = vec4(u_Color, 1.f);
			}
		)";

		m_FlatColorShader = Lily::Shader::Create("FlatColor", flatColorShaderVertexSrc, flatColorShaderFragmentSrc);


		auto textureShader = m_ShaderLibrary.Load("assets/shaders/Texture.glsl");

		m_Texture = Lily::Texture2D::Create("assets/textures/pistol.png");
		m_Texture2 = Lily::Texture2D::Create("assets/textures/medical.png");

		std::dynamic_pointer_cast<Lily::OpenGLShader>(textureShader)->Bind();
		std::dynamic_pointer_cast<Lily::OpenGLShader>(textureShader)->UploadUniformInt("u_Texture", 0);
	}

	void OnUpdate(Lily::Timestep ts) override
	{
		// Update
		//LL_TRACE("Delta time: {0}s {1}ms", ts.GetSeconds(), ts.GetMilliSeconds());

		m_CameraController.OnUpdate(ts);

		// Render
		Lily::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Lily::RenderCommand::Clear();

		Lily::Renderer::BeginScene(m_CameraController.GetCamera());

		static glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		std::dynamic_pointer_cast<Lily::OpenGLShader>(m_FlatColorShader)->Bind();
		std::dynamic_pointer_cast<Lily::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color", m_SquareColor);

		for (int y = 0; y < 20; y++)
		{
			for (int x = 0; x < 20; x++)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.f);
				glm::mat4 transform = glm::translate(glm::mat4(1.f), pos) * scale;
				Lily::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
			}
		}

		auto textureShader = m_ShaderLibrary.Get("Texture");

		m_Texture->Bind();
		Lily::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		m_Texture2->Bind();
		Lily::Renderer::Submit(textureShader, m_SquareVA,
			glm::translate(glm::mat4(1.f), glm::vec3(0.25f, -0.25f, 0.f)) * glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		// Triangle
		//Lily::Renderer::Submit(m_Shader, m_VertexArray);

		Lily::Renderer::EndScene();
	}

	void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}

	void OnEvent(Lily::Event& e) override
	{
		m_CameraController.OnEvent(e);
	}

	
private:
	Lily::ShaderLibrary m_ShaderLibrary;

	Lily::Ref<Lily::Shader> m_Shader;
	Lily::Ref<Lily::VertexArray> m_VertexArray;

	Lily::Ref<Lily::Shader> m_FlatColorShader;
	Lily::Ref<Lily::VertexArray> m_SquareVA;

	Lily::Ref<Lily::Texture2D> m_Texture;
	Lily::Ref<Lily::Texture2D> m_Texture2;

	Lily::OrthographicCameraController m_CameraController;

	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
};

class Sandbox : public Lily::Application
{
public:
	Sandbox()
	{
		//PushLayer(new ExampleLayer());
		PushLayer(new Sandbox2D());
	}

	~Sandbox()
	{

	}
};

Lily::Application* Lily::CreateApplication()
{
	return new Sandbox();
}