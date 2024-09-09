#include "Quiet_PCH.h"
#include "Camera.h"

#include "Core/Application.h"
#include "Core/Input.h"

namespace Quiet
{
	Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch) : 
		Front(glm::vec3(0.0f, 0.0f, -1.0f)),
		MovementSpeed(SPEED),
		MouseSensitivity(SENSITIVITY),
		Zoom(ZOOM)
	{
		Position = position;
		WorldUp = up;
		Yaw = yaw;
		Pitch = pitch;

		UpdateCameraVectors();
	}

	void Camera::OnUpdate(float deltaTime)
	{
		float velocity = MovementSpeed * deltaTime;

		if (Input::IsKeyPressed(Key::W)) Position += Front * velocity;
		if (Input::IsKeyPressed(Key::S)) Position -= Front * velocity;
		if (Input::IsKeyPressed(Key::A)) Position -= Right * velocity;
		if (Input::IsKeyPressed(Key::D)) Position += Right * velocity;

		Position.y = 0.0f;
	}

	void Camera::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<MouseMovedEvent>(BIND_EVENT_FN(Camera::OnMouseMoved));
	}

	glm::mat4 Camera::GetViewMatrix()
	{
		return glm::lookAt(Position, Position + Front, Up);
	}

	void Camera::UpdateCameraVectors()
	{
		// Calculate the new Front vector from the Camera's Euler Angles
		glm::vec3 front;
		front.x = cos(glm::radians(Yaw) * cos(glm::radians(Pitch)));
		front.y = sin(glm::radians(Pitch));
		front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
		Front = glm::normalize(front);

		// Recalculate the Right and Up vectors
		Right	= glm::normalize(glm::cross(Front, WorldUp));
		Up		= glm::normalize(glm::cross(Right, Front));
	}

	bool Camera::OnMouseMoved(MouseMovedEvent& event)
	{
		float xpos = event.GetX();
		float ypos = event.GetY();

		if (firstMouse) {  // If this is the first frame, initialize the lastX and lastY
			lastX = xpos;
			lastY = ypos;
			firstMouse = false;
		}

		// Calculate the change in mouse positions (delta)
		float xOffset = xpos - lastX;
		float yOffset = lastY - ypos;  // Reversed because y-coordinates go from bottom to top in OpenGL

		lastX = xpos;
		lastY = ypos;

		// Apply sensitivity to the offset values
		xOffset *= MouseSensitivity;
		yOffset *= MouseSensitivity;

		// Adjust the yaw and pitch using the offsets
		Yaw += xOffset;
		Pitch += yOffset;

		if (Pitch > 89.0f) 	Pitch = 89.0f;
		if (Pitch < -89.0f)	Pitch = -89.0f;

		UpdateCameraVectors();

		return false;
	}
}
