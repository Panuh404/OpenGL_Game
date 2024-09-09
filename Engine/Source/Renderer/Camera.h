#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Event/ApplicationEvent.h"
#include "Event/MouseEvent.h"

namespace Quiet
{
	// Possible options for camera movement
	enum CameraMovement
	{
		FORWARD,
		BACKWARD,
		LEFT,
		RIGHT
	};

	// Camera Values
	constexpr float YAW			= -90.0f;
	constexpr float PITCH		= 0.0f;
	constexpr float SPEED		= 2.5f;
	constexpr float SENSITIVITY = 0.1f;
	constexpr float ZOOM		= 45.0f;

	class Camera
	{
	public:
		Camera(glm::vec3 position = glm::vec3(0.0f,0.0f,0.0f), glm::vec3 up = glm::vec3(0.0f,1.0f,0.0f), float yaw = YAW, float pitch = PITCH);

		void OnUpdate(float deltaTime);
		void OnEvent(Event& event);

		glm::mat4 GetViewMatrix();

	public:
		// camera options
		float MovementSpeed;
		float MouseSensitivity;
		float Zoom;

		// camera Attributes
		glm::vec3 Position;
		glm::vec3 Front;
		glm::vec3 Up;
		glm::vec3 Right;
		glm::vec3 WorldUp;

		// euler Angles
		float Yaw;
		float Pitch;

	private:
		void UpdateCameraVectors();
		bool OnMouseMoved(MouseMovedEvent& event);

		float lastX = 0.0f, lastY = 0.0f;
		bool firstMouse = true;
	};
}
