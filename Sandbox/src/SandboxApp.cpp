#include "Lily.h"

#include "imgui/imgui.h"

class ExampleLayer : public Lily::Layer 
{
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.f)
	{
		m_VertexArray.reset(Lily::VertexArray::Create());

		float vertices[] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			0.0f, 0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		std::shared_ptr<Lily::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Lily::VertexBuffer::Create(vertices, sizeof(vertices)));

		Lily::BufferLayout layout = {
			{ Lily::ShaderDataType::Float3, "a_Position" },
			{ Lily::ShaderDataType::Float4, "a_Color" }
		};
		vertexBuffer->SetLayout(layout);

		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		std::shared_ptr<Lily::IndexBuffer> indexBuffer;
		indexBuffer.reset(Lily::IndexBuffer::Create(indices, 3));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA.reset(Lily::VertexArray::Create());

		float squareVertices[] = {
			-0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.5f, 0.5f, 0.0f,
			-0.5f, 0.5f, 0.0f
		};

		std::shared_ptr<Lily::VertexBuffer> squareVB;
		squareVB.reset(Lily::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

		squareVB->SetLayout({
			{ Lily::ShaderDataType::Float3, "a_Position" }
			});

		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<Lily::IndexBuffer> squareIB;
		squareIB.reset(Lily::IndexBuffer::Create(squareIndices, 6));
		m_SquareVA->SetIndexBuffer(squareIB);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;

			out vec3 v_Position;
			out vec4 v_Color;
			
			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
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

		m_Shader.reset(new Lily::Shader(vertexSrc, fragmentSrc));

		std::string blueShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;

			out vec3 v_Position;
			
			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
			}
		)";  // location = 0 means at index 0, a means attribute

		std::string blueShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			
			in vec3 v_Position;

			void main()
			{
				color = vec4(0.2, 0.3, 0.8, 1.0);
			}
		)";

		m_BlueShader.reset(new Lily::Shader(blueShaderVertexSrc, blueShaderFragmentSrc));
	}

	void OnUpdate() override
	{
		if (Lily::Input::IsKeyPressed(LL_KEY_LEFT))
			m_CameraPosition.x -= m_CameraMoveSpeed;

		else if (Lily::Input::IsKeyPressed(LL_KEY_RIGHT))
			m_CameraPosition.x += m_CameraMoveSpeed;

		if (Lily::Input::IsKeyPressed(LL_KEY_DOWN))
			m_CameraPosition.y -= m_CameraMoveSpeed;

		else if (Lily::Input::IsKeyPressed(LL_KEY_UP))
			m_CameraPosition.y += m_CameraMoveSpeed;

		if (Lily::Input::IsKeyPressed(LL_KEY_A))
			m_CameraRotation += m_CameraRotationSpeed;

		else if (Lily::Input::IsKeyPressed(LL_KEY_D))
			m_CameraRotation -= m_CameraRotationSpeed;

		Lily::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Lily::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		Lily::Renderer::BeginScene(m_Camera);
		
		Lily::Renderer::Submit(m_BlueShader, m_SquareVA);

		Lily::Renderer::Submit(m_Shader, m_VertexArray);

		Lily::Renderer::EndScene();
	}

	void OnImGuiRender() override
	{

	}

	void OnEvent(Lily::Event& event) override
	{

	}

	
private:
	std::shared_ptr<Lily::Shader> m_Shader;
	std::shared_ptr<Lily::VertexArray> m_VertexArray;

	std::shared_ptr<Lily::Shader> m_BlueShader;
	std::shared_ptr<Lily::VertexArray> m_SquareVA;

	Lily::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraRotation = 0.0f;
	float m_CameraMoveSpeed = 0.1f;
	float m_CameraRotationSpeed = 2.0f;
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