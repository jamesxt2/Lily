#pragma once

#include "Lily/Renderer/OrthographicCamera.h"
#include "Lily/Core/Timestep.h"

#include "Lily/Events/ApplicationEvent.h"
#include "Lily/Events/MouseEvent.h"

namespace Lily {

	class OrthographicCameraController
	{
	public:
		OrthographicCameraController(float aspectRatio, bool rotation = false);

		void OnUpdate(Timestep ts);
		void OnEvent(Event& e);

		OrthographicCamera& GetCamera() { return m_Camera; }
		const OrthographicCamera& GetCamera() const { return m_Camera; }

		inline void SetZoomLevel(float level) { m_ZoomLevel = level; }
		inline float GetZoomLevel(float level) { return m_ZoomLevel; }
	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);

		float m_AspectRatio;
		float m_ZoomLevel = 1.f;
		OrthographicCamera m_Camera;

		bool m_Rotation;

		glm::vec3 m_CameraPosition{ 0.f, 0.f, 0.f };
		float m_CameraRotation{ 0.f };
		float m_CameraTranslationSpeed{ 5.f };
		float m_CameraRotationSpeed{ 180.f };
	};

}