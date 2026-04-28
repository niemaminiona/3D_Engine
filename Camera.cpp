#include "Camera.h"

Camera::Camera(int width, int height, glm::vec3 position, Shader& shader)
	: width(width), height(height), position(position), shader(shader) { Update(); }

void Camera::Update() {
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	front = glm::normalize(front);

	right = glm::normalize(glm::cross(front, glm::vec3(0.0f, 1.0f, 0.0f)));
	up = glm::normalize(glm::cross(right, front));

    view = glm::lookAt(position, position + front, up);
    projection = glm::perspective(glm::radians(FOV), (GLfloat)width / (GLfloat)height, zNear, zFar);

    shader.setUniformMatrix4("view", view);
    shader.setUniformMatrix4("projection", projection);
}



void Camera::HandleKeyInputs(GLFWwindow* window) {
	// W, S, A, D
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		position += front * moveSpeed;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		position -= front * moveSpeed;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		position -= right * moveSpeed;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		position += right * moveSpeed;
	}

	// SHIFT, SPACE
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		position += glm::vec3(0.0f, 1.0f, 0.0f) * moveSpeed;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		position -= glm::vec3(0.0f, 1.0f, 0.0f) * moveSpeed;
	}

	// Arrows
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
		pitch += turnSpeed;
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		pitch -= turnSpeed;
	}
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
		yaw += turnSpeed;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
		yaw -= turnSpeed;
	}
}
