#include "Lux.h"
#include "Lux/Layer.h"
#include "Lux/Renderer/Buffer.h"
#include "Lux/Renderer/Shader.h"
#include "Lux/Renderer/Camera.h"
#include "Lux/Events/KeyEvent.h"
#include "Lux/KeyCodes.h"
#include "Lux/Input.h"

class ExampleLayer : public Lux::Layer
{
public:
	ExampleLayer()
		:Layer("Example"), m_Camera(std::make_shared<Lux::Camera>(-1.6f, 1.6f, -0.9f, 0.9f)) {}

	virtual void OnAttach() override
	{
		m_TraingleShader = std::make_shared<Lux::Shader>("D:/Documents/VisualStudio/Projects/Lux/Lux/Resources/TriangleFragmentShader.shader",
			"D:/Documents/VisualStudio/Projects/Lux/Lux/Resources/TriangleVertexShader.shader");

		m_SquareShader = std::make_shared<Lux::Shader>("D:/Documents/VisualStudio/Projects/Lux/Lux/Resources/SquareFragmentShader.shader",
			"D:/Documents/VisualStudio/Projects/Lux/Lux/Resources/SquareVertexShader.shader");

		float squareVertices[] =
		{
			 -0.75f, -0.75f, 0.f, 0.f,  0.4f, 0.8f, 1.f,
			  0.75f, -0.75f, 0.f, 0.f,  0.4f, 0.8f, 1.f,
			  0.75f,  0.75f, 0.f, 0.f,  0.4f, 0.8f, 1.f,
			 -0.75f,  0.75f, 0.f, 0.f,  0.4f, 0.8f, 1.f,
			 -2.75f,  0.75f, 0.f, 0.f,  0.4f, 0.8f, 1.f,
			 -0.75f,  0.75f, 0.f, 0.f,  0.4f, 0.8f, 1.f,
			 -0.75f,  2.75f, 0.f, 0.f,  0.4f, 0.8f, 1.f
		};

		float traingleVertices[] =
		{
			-0.5f,   0.75f,  0.f, 0.8f, 0.2f, 0.8f, 1.f,
			 0.5f,   0.75f,  0.f, 0.3f, 0.2f, 0.8f, 1.f,
			 0.f,    1.5f,   0.f, 0.8f, 0.8f, 0.2f, 1.f
		};

		m_TraingleVertexBuffer.reset(Lux::VertexBuffer::Create(traingleVertices, sizeof(traingleVertices)));

		m_TraingleVertexBuffer->SetLayout({
			{ Lux::ShaderDataType::Float3, "a_Position" },
			{ Lux::ShaderDataType::Float4, "a_Color" }
			});

		m_SquareVertexBuffer.reset(Lux::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

		m_SquareVertexBuffer->SetLayout({
			{ Lux::ShaderDataType::Float3, "a_Position" },
			{ Lux::ShaderDataType::Float4, "a_Color" }
			});

		uint32_t squareIndices[] =
		{
			0, 1, 2, 0, 2, 3
		};

		uint32_t traingleIndices[] =
		{
			0, 1, 2
		};

		m_TriangleIndexBuffer.reset(Lux::IndexBuffer::Create(traingleIndices, sizeof(traingleIndices) / sizeof(uint32_t)));

		m_TriangleVertexArray = Lux::VertexArray::Create(m_TraingleVertexBuffer, m_TriangleIndexBuffer);

		m_SquareIndexBuffer.reset(Lux::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));

		m_SquareVertexArray = Lux::VertexArray::Create(m_SquareVertexBuffer, m_SquareIndexBuffer);
	}

	virtual void OnEvent(Lux::Event& e)
	{
	}

	virtual void OnUpdate(float DeltaTime) override
	{
		if (Lux::Input::IsKeyPressed(LX_KEY_W) || Lux::Input::IsKeyPressed(LX_KEY_UP))
			m_Camera->AddCameraLocationLocal(glm::vec3( 0.f, m_CameraMoveSpeed, 0.f ) * DeltaTime);
		else if (Lux::Input::IsKeyPressed(LX_KEY_S) || Lux::Input::IsKeyPressed(LX_KEY_DOWN))
			m_Camera->AddCameraLocationLocal(glm::vec3( 0.f, -m_CameraMoveSpeed, 0.f) * DeltaTime);
		if (Lux::Input::IsKeyPressed(LX_KEY_D) || Lux::Input::IsKeyPressed(LX_KEY_RIGHT))
			m_Camera->AddCameraLocationLocal(glm::vec3( m_CameraMoveSpeed, 0.f, 0.f) * DeltaTime);
		else if (Lux::Input::IsKeyPressed(LX_KEY_A) || Lux::Input::IsKeyPressed(LX_KEY_LEFT))
			m_Camera->AddCameraLocationLocal(glm::vec3( -m_CameraMoveSpeed, 0.f, 0.f) * DeltaTime);

		if (Lux::Input::IsKeyPressed(LX_KEY_Q))
			m_Camera->AddCameraRotation(m_CameraRotateSpeed * DeltaTime);
		if (Lux::Input::IsKeyPressed(LX_KEY_E))
			m_Camera->AddCameraRotation(-m_CameraRotateSpeed * DeltaTime);

		Lux::Renderer::BeginScene(m_Camera->GetProjectionMatrix() * m_Camera->GetViewMatrix());

		Lux::Renderer::Submit(m_TriangleVertexArray, m_TraingleShader);
		Lux::Renderer::Submit(m_SquareVertexArray, m_SquareShader);

		Lux::Renderer::EndScene();
	}

private:
	std::shared_ptr<Lux::VertexBuffer> m_SquareVertexBuffer;
	std::shared_ptr<Lux::IndexBuffer> m_SquareIndexBuffer;
	std::shared_ptr<Lux::VertexArray> m_SquareVertexArray;
	std::shared_ptr<Lux::Shader> m_SquareShader;
	std::shared_ptr<Lux::VertexBuffer> m_TraingleVertexBuffer;
	std::shared_ptr<Lux::IndexBuffer> m_TriangleIndexBuffer;
	std::shared_ptr<Lux::VertexArray> m_TriangleVertexArray;
	std::shared_ptr<Lux::Shader> m_TraingleShader;
	std::shared_ptr<Lux::Camera> m_Camera;

	float m_CameraMoveSpeed = 5.f;
	float m_CameraRotateSpeed = 180.f;
};

class Sandbox : public Lux::Application
{
public:
	Sandbox() 
	{
		PushLayer(new ExampleLayer());
	}
	~Sandbox() {}
};

Lux::Application* Lux::CreateApplication()
{
	return new Sandbox();
}
