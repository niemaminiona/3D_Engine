#include "Camera.h"

Camera::Camera(int width, int height, glm::vec3 position, Shader& shader)
	: width(width), height(height), position(position), shader(shader) { Update(); }

void Camera::Update() {
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	front = glm::normalize(front);

	frontXZ = glm::normalize(glm::vec3(front.x, 0.0f, front.z));

	right = glm::normalize(glm::cross(front, glm::vec3(0.0f, 1.0f, 0.0f)));
	up = glm::normalize(glm::cross(right, front));

    view = glm::lookAt(position, position + front, up);
    projection = glm::perspective(glm::radians(FOV), (GLfloat)width / (GLfloat)height, zNear, zFar);

    shader.setUniformMatrix4("view", view);
    shader.setUniformMatrix4("projection", projection);
}

void Camera::HandleAllInputs(GLFWwindow* window) {
	HandleKeyInputs(window);
	HandleMouseInputs(window);
}


void Camera::HandleKeyInputs(GLFWwindow* window) {
	// W, S, A, D
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		position += frontXZ * moveSpeed;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		position -= frontXZ * moveSpeed;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		position -= right * moveSpeed;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		position += right * moveSpeed;
	}

	// SHIFT, SPACE, CTRL
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		position += glm::vec3(0.0f, 1.0f, 0.0f) * moveSpeed;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
	{
		position -= glm::vec3(0.0f, 1.0f, 0.0f) * moveSpeed;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		moveSpeed = 0.2f;
	}
	else {
		moveSpeed = defaultMoveSpeed;
	}

	// Arrows
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
		pitch += turnSpeed;
		pitch = glm::clamp(pitch, -89.0f, 89.0f);
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		pitch -= turnSpeed;
		pitch = glm::clamp(pitch, -89.0f, 89.0f);
	}
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
		yaw += turnSpeed;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
		yaw -= turnSpeed;
	}
}

void Camera::HandleMouseInputs(GLFWwindow* window) {
	// switching between modes
	bool currentLeft = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS;
	if (currentLeft && !lastLeftMouseState)
	{
		mouseFocusedMode = !mouseFocusedMode;
		if (mouseFocusedMode)
		{
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			firstMouse = true;
		}
		else
		{
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}
	}
	lastLeftMouseState = currentLeft;

	// camera movement
	if (mouseFocusedMode) {
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

		if (firstMouse)
		{
			lastX = xpos;
			lastY = ypos;
			firstMouse = false;
		}

		double xoffset = xpos - lastX;
		double yoffset = lastY - ypos;

		lastX = xpos;
		lastY = ypos;

		xoffset *= sensitivity;
		yoffset *= sensitivity;

		yaw += (float)xoffset;
		pitch += (float)yoffset;

		pitch = glm::clamp(pitch, -89.0f, 89.0f);
	}
}
