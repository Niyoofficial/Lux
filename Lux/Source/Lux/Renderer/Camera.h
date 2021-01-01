#pragma once

#include <D:\Documents\VisualStudio\Projects\Lux\Lux\Vendor\glm\glm\glm.hpp>

namespace Lux
{
	class Camera
	{
	public:
		Camera(float left, float right, float top, float bottom);

		void OnUpdate(float DeltaTime);

		void AddCameraRotation(float rotation);
		void SetCameraRotation(float rotation);
		void AddCameraLocationLocal(glm::vec3 location);
		void SetCameraLocation(glm::vec3 location);

		inline const glm::vec3& GetPosition() const { return m_Position; }

		inline const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
		inline const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
	private:
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ProjectionMatrix;

		glm::vec3 m_Position = { 0.f, 0.f, 0.f };
		float m_Rotation = 0.f;
	};
}