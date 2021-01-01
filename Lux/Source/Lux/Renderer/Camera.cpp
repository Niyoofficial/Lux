#include "lxpch.h"
#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>

namespace Lux
{
	Camera::Camera(float left, float right, float bottom, float top)
		:m_ProjectionMatrix(glm::ortho(left, right, bottom, top)), m_ViewMatrix(1.f)
	{
	}

	void Camera::OnUpdate(float DeltaTime)
	{
	}

	void Camera::AddCameraRotation(float rotation)
	{
		m_Rotation += glm::radians(rotation);
		m_ViewMatrix = glm::inverse(glm::translate(glm::mat4(1.f), m_Position) * glm::rotate(glm::mat4(1.f), m_Rotation, glm::vec3(0.f, 0.f, 1.f)));
	}

	void Camera::SetCameraRotation(float rotation)
	{
		m_Rotation = glm::radians(rotation);
		m_ViewMatrix = glm::inverse(glm::translate(glm::mat4(1.f), m_Position) * glm::rotate(glm::mat4(1.f), m_Rotation, glm::vec3(0.f, 0.f, 1.f)));
	}

	void Camera::AddCameraLocationLocal(glm::vec3 location)
	{
		location = glm::rotate(location, m_Rotation, glm::vec3(0.f, 0.f, 1.f));
		m_Position += location;
		m_ViewMatrix = glm::inverse(glm::translate(glm::mat4(1.f), m_Position) * glm::rotate(glm::mat4(1.f), m_Rotation, glm::vec3(0.f, 0.f, 1.f)));
	}

	void Camera::SetCameraLocation(glm::vec3 location)
	{
		m_Position = location;
		m_ViewMatrix = glm::inverse(glm::translate(glm::mat4(1.f), m_Position) * glm::rotate(glm::mat4(1.f), m_Rotation, glm::vec3(0.f, 0.f, 1.f)));
	}
}
