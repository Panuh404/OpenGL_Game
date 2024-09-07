#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

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
		Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);

		glm::mat4 GetViewMatrix();

		void KeyboardEvents(CameraMovement direction, float deltaTime);
		void MouseEvents(float xOffset, float yOffset, GLboolean constrainPitch = true);
		void MouseWheelEvents(float yOffset);

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
	};
}